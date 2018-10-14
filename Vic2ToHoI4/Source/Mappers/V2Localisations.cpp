/*Copyright (c) 2017 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "V2Localisations.h"
#include <fstream>
#include "../Configuration.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "Object.h"



V2Localisations* V2Localisations::instance = NULL;



V2Localisations::V2Localisations():
	localisations(),
	localisationToKeyMap()
{
	LOG(LogLevel::Info) << "Reading localisation";

	ReadFromAllFilesInFolder(Configuration::getV2Path() + "/localisation");

	for (auto mod: Configuration::getVic2Mods())
	{
		LOG(LogLevel::Debug) << "Reading mod localisation";
		ReadFromAllFilesInFolder(Configuration::getV2Path() + "/mod/" + mod + "/localisation");
	}
}


void V2Localisations::ReadFromAllFilesInFolder(const string& folderPath)
{
	set<string> fileNames;
	Utils::GetAllFilesInFolder(folderPath, fileNames);

	for (const auto& fileName: fileNames)
	{
		ReadFromFile(folderPath + '/' + fileName);
	}
}


void V2Localisations::ReadFromFile(const string& fileName)
{
	ifstream in(fileName);

	while (!in.eof())
	{
		string line;
		getline(in, line);
		if (line[0] != '#')
		{
			processLine(line);
		}
	}

	in.close();
}


const string languages[] = { "english", "french", "german", "polish", "spanish", "italian", "swedish", "czech", "hungarian", "dutch", "braz_por", "russian", "finnish" };
void V2Localisations::processLine(string line)
{
	int division = line.find_first_of(';');
	string key = line.substr(0, division);

	for (auto language: languages)
	{
		string result = getNextLocalisation(line, division);
		result = replaceBadCharacters(result);
		auto UTF8Result = Utils::convert8859_15ToUTF8(result);

		if (language == "english")
		{
			localisationToKeyMap[UTF8Result] = key;
		}
		localisations[key][language] = UTF8Result;
	}
}


string V2Localisations::getNextLocalisation(string line, int& division)
{
	int frontDivision = division + 1;
	division = line.find_first_of(';', frontDivision);
	return line.substr(frontDivision, division - frontDivision);
}


string V2Localisations::replaceBadCharacters(string localisation)
{
	// Ö gets translated to an invalid character sequence. Oe is accepted substitute in German.
	int O = localisation.find_first_of("Ö");
	while (O != string::npos)
	{
		localisation.replace(O, 1, "Oe");
		O = localisation.find_first_of("Ö");
	}

	// dash characters other than 0x2D break HoI4
	int dash = localisation.find_first_of("–");
	while (dash != string::npos)
	{
		localisation.replace(dash, 1, "-");
		dash = localisation.find_first_of("–");
	}

	// Problem with S-hacek
	int shacek = localisation.find_first_of("");	// character may not display, but is present
	while (shacek != string::npos)
	{
		localisation.replace(shacek, 1, "š");
		shacek = localisation.find_first_of("");	// character may not display, but is present
	}

	// Problem with Z-hacek
	int zhacek = localisation.find_first_of("");	// character may not display, but is present
	while (zhacek != string::npos)
	{
		localisation.replace(zhacek, 1, "ž");
		zhacek = localisation.find_first_of("");	// character may not display, but is present
	}

	// Problem with apostrophe (Spanish)
	int apostrophe = localisation.find_first_of("");	// character may not display, but is present
	while (apostrophe != string::npos)
	{
		localisation.replace(apostrophe, 1, "’");
		apostrophe = localisation.find_first_of("");	// character may not display, but is present
	}

	return localisation;
}


void V2Localisations::ActuallyUpdateDomainCountry(const string& tag, const string& domainName)
{
	LanguageToLocalisationMap regionLocalisations;
	const auto domainKey = localisationToKeyMap.find(domainName);
	if (domainKey != localisationToKeyMap.end())
	{
		const auto domainLocalisations = localisations.find(domainKey->second);
		if (domainLocalisations != localisations.end())
		{
			for (auto regionInLanguage: domainLocalisations->second)
			{
				regionLocalisations.insert(regionInLanguage);
			}
		}
	}

	const auto KeyToLocalisationsMappings = localisations.find(tag);
	if (KeyToLocalisationsMappings == localisations.end())
	{
		return;
	}
	auto nameInAllLanguages = KeyToLocalisationsMappings->second;

	for (auto nameInLanguage : nameInAllLanguages)
	{
		string replacementName = domainName;
		auto replacementLocalisation = regionLocalisations.find(nameInLanguage.first);
		if (replacementLocalisation != regionLocalisations.end())
		{
			replacementName = replacementLocalisation->second;
		}
		else
		{
			LOG(LogLevel::Warning) << "Could not find regions localisation for " << domainName << " in " << nameInLanguage.first;
		}
		string updatedName = nameInLanguage.second;
		size_t regionPos = updatedName.find("$REGION$");
		if (regionPos != string::npos)
		{
			updatedName.replace(regionPos, 8, replacementName);
			KeyToLocalisationsMappings->second[nameInLanguage.first] = updatedName;
		}
	}
}


const optional<string> V2Localisations::ActuallyGetTextInLanguage(const string& key, const string& language) const
{
	const auto KeyToLocalisationsMapping = localisations.find(key);
	if (KeyToLocalisationsMapping == localisations.end())
	{
		return {};
	}

	const auto LanguageToLocalisationMapping = KeyToLocalisationsMapping->second.find(language);
	if (LanguageToLocalisationMapping == KeyToLocalisationsMapping->second.end())
	{
		return {};
	}

	return LanguageToLocalisationMapping->second;
}


const map<string, string> V2Localisations::ActuallyGetTextInEachLanguage(const string& key) const
{
	static const map<string, string> noLocalisations;

	const auto KeyToLocalisationsMappings = localisations.find(key);
	if (KeyToLocalisationsMappings == localisations.end())
	{
		return noLocalisations;
	}
	else
	{
		return KeyToLocalisationsMappings->second;
	}
}

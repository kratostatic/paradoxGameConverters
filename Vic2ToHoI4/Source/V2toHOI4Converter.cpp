/*Copyright (c) 2018 The Paradox Game Converters Project

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



#include <algorithm>
#include <fstream>
#include <stdexcept>
#include "Configuration.h"
#include "Flags.h"
#include "Log.h"
#include "HOI4World/HoI4World.h"
#include "V2World/World.h"
#include "OSCompatibilityLayer.h"



void ConvertV2ToHoI4(const string& V2SaveFileName);
int main(const int argc, const char* argv[])
{
	try
	{
		LOG(LogLevel::Info) << "Converter version 0.2G";
		LOG(LogLevel::Info) << "Built on " << __DATE__ << " at " << __TIME__;
		LOG(LogLevel::Info) << "Current directory is " << Utils::getCurrentDirectory();

		const char* const defaultV2SaveFileName = "input.v2";
		string V2SaveFileName;
		if (argc >= 2)
		{
			V2SaveFileName = argv[1];
			LOG(LogLevel::Info) << "Using input file " << V2SaveFileName;
		}
		else
		{
			V2SaveFileName = defaultV2SaveFileName;
			LOG(LogLevel::Info) << "No input file given, defaulting to " << defaultV2SaveFileName;
		}

		ConvertV2ToHoI4(V2SaveFileName);

		return 0;
	}

	catch (const std::exception& e)
	{
		LOG(LogLevel::Error) << e.what();
		return -1;
	}
}


void checkMods();
void getOutputName(const string& V2SaveFileName);
void output(const HoI4World& destWorld);
void ConvertV2ToHoI4(const string& V2SaveFileName)
{
	Configuration::getInstance();

	checkMods();
	getOutputName(V2SaveFileName);

	Vic2::World sourceWorld(V2SaveFileName);
	HoI4World destWorld(&sourceWorld);

	output(destWorld);
	LOG(LogLevel::Info) << "* Conversion complete *";
}


void checkMods()
{
	LOG(LogLevel::Info) << "Double-checking Vic2 mods";

	set<string> fileNames;
	Utils::GetAllFilesInFolder(Configuration::getV2Path() + "/mod", fileNames);
	for (auto fileName: fileNames)
	{
		const int lastPeriodPos = fileName.find_last_of('.');
		if (fileName.substr(lastPeriodPos, fileName.length()) == ".mod")
		{
			string folderName = fileName.substr(0, lastPeriodPos);
			if (Utils::doesFolderExist(Configuration::getV2Path() + "/mod/" + folderName))
			{
				LOG(LogLevel::Debug) << "Found mod with name " << folderName;
			}
		}
	}

	for (auto expectedMod: Configuration::getVic2Mods())
	{
		LOG(LogLevel::Debug) << "Expecting a mod with name " << expectedMod;
		if (!Utils::doesFolderExist(Configuration::getV2Path() + "/mod/" + expectedMod))
		{
			LOG(LogLevel::Error) << "Could not find expected mod";
			exit(-1);
		}
	}
}


void getOutputName(const string& V2SaveFileName)
{
	int slash = V2SaveFileName.find_last_of("\\");
	if (slash == string::npos)
	{
		slash = V2SaveFileName.find_last_of("/");
	}
	string outputName = V2SaveFileName.substr(slash + 1, V2SaveFileName.length());
	const int length = outputName.find_first_of(".");
	outputName = outputName.substr(0, length);

	std::replace(outputName.begin(), outputName.end(), '-', '_');
	std::replace(outputName.begin(), outputName.end(), ' ', '_');

	Configuration::setOutputName(outputName);
	LOG(LogLevel::Info) << "Using output name " << outputName;

	string outputFolder = Utils::getCurrentDirectory() + "/output/" + Configuration::getOutputName();
	if (Utils::doesFolderExist(outputFolder))
	{
		if (!Utils::deleteFolder(outputFolder))
		{
			exit(-1);
		}
	}
}


void createModFile();
void renameOutputFolder();
void output(const HoI4World& destWorld)
{
	createModFile();
	renameOutputFolder();
	copyFlags(destWorld.getCountries());
	destWorld.output();
}


void createModFile()
{
	LOG(LogLevel::Info) << "Outputting mod";
	if (!Utils::copyFolder("blankMod/output", "output/output"))
	{
		exit(-1);
	}

	ofstream modFile("output/" + Configuration::getOutputName() + ".mod");
	if (!modFile.is_open())
	{
		LOG(LogLevel::Error) << "Could not create .mod file";
		exit(-1);
	}

	HoI4::Version versionThatWantsBOM("1.3.3");
	HoI4::Version thisVersion = Configuration::getHOI4Version();
	if (thisVersion >= versionThatWantsBOM)
	{
		modFile << "\xEF\xBB\xBF";    // add the BOM to make HoI4 happy
	}
	modFile << "name = \"Converted - " << Configuration::getOutputName() << "\"\n";
	modFile << "path = \"mod/" << Configuration::getOutputName() << "/\"\n";
	modFile << "user_dir = \"" << Configuration::getOutputName() << "_user_dir\"\n";
	modFile << "replace_path=\"common/ideologies\"\n";
	modFile << "replace_path=\"history/countries\"\n";
	modFile << "replace_path=\"history/states\"\n";
	modFile << "supported_version=\"" << thisVersion << "\"";
	modFile.close();
}


void renameOutputFolder()
{
	if (!Utils::renameFolder("output/output", "output/" + Configuration::getOutputName()))
	{
		LOG(LogLevel::Error) << "Could not rename output folder!";
		exit(-1);
	}
}
/*Copyright(c) 2017 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */



#include "EU4Diplomacy.h"
#include "Log.h"
#include "Object.h"



EU4Agreement::EU4Agreement(shared_ptr<Object> obj)
{
	type = obj->getKey();

	std::vector<shared_ptr<Object>> objType = obj->getValue("subject_type");
	if (objType.size() > 0)
	{
		type = objType[0]->getLeaf();

		if (type == "personal_union")
		{
			type = "union";
		}
		if ((type == "client_vassal") || (type == "daimyo_vassal"))
		{
			type = "vassal";
		}
		if (type == "dependency")
		{
			LOG(LogLevel::Warning) << "Dependency has no subject type";
		}
	}


	std::vector<shared_ptr<Object>> objFirst = obj->getValue("first");
	if (objFirst.size() > 0)
	{
		country1 = objFirst[0]->getLeaf();
	}
	else
	{
		LOG(LogLevel::Warning) << "Diplomatic agreement (" << type << ") has no first party";
	}

	std::vector<shared_ptr<Object>> objSecond = obj->getValue("second");
	if (objSecond.size() > 0)
	{
		country2 = objSecond[0]->getLeaf();
	}
	else
	{
		LOG(LogLevel::Warning) << "Diplomatic agreement (" << type << ") has no second party";
	}

	std::vector<shared_ptr<Object>> objDate = obj->getValue("start_date");
	if (objDate.size() > 0)
	{
		startDate = date(objDate[0]->getLeaf());
	}
}


EU4Diplomacy::EU4Diplomacy()
{
	agreements.clear();
}


EU4Diplomacy::EU4Diplomacy(shared_ptr<Object> obj)
{
	std::vector<shared_ptr<Object>> objRMs = obj->getValue("royal_marriage");
	for (std::vector<shared_ptr<Object>>::iterator itr = objRMs.begin(); itr != objRMs.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objGaurantees = obj->getValue("guarantee");
	for (std::vector<shared_ptr<Object>>::iterator itr = objGaurantees.begin(); itr != objGaurantees.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objVassals = obj->getValue("vassal");
	for (std::vector<shared_ptr<Object>>::iterator itr = objVassals.begin(); itr != objVassals.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objProtectorate = obj->getValue("protectorate");
	for (std::vector<shared_ptr<Object>>::iterator itr = objProtectorate.begin(); itr != objProtectorate.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objColonial = obj->getValue("is_colonial");
	for (std::vector<shared_ptr<Object>>::iterator itr = objColonial.begin(); itr != objColonial.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objMarch = obj->getValue("is_march");
	for (std::vector<shared_ptr<Object>>::iterator itr = objMarch.begin(); itr != objMarch.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objSpheres = obj->getValue("sphere");
	for (std::vector<shared_ptr<Object>>::iterator itr = objSpheres.begin(); itr != objSpheres.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objAlliances = obj->getValue("alliance");
	for (std::vector<shared_ptr<Object>>::iterator itr = objAlliances.begin(); itr != objAlliances.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objUnions = obj->getValue("union");
	for (std::vector<shared_ptr<Object>>::iterator itr = objUnions.begin(); itr != objUnions.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}

	std::vector<shared_ptr<Object>> objDependencies = obj->getValue("dependency");
	for (std::vector<shared_ptr<Object>>::iterator itr = objDependencies.begin(); itr != objDependencies.end(); ++itr)
	{
		EU4Agreement agr(*itr);		// the new agreement
		agreements.push_back(agr);
	}
}



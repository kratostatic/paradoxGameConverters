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



#include "HoI4Army.h"
#include "Log.h"
#include "../Configuration.h"
#include "ParadoxParserUTF8.h"
#include <sstream>



//HoI4RegimentType::HoI4RegimentType(string type)
//{
//	/*string	filename	= Configuration::getHoI4Path() + "/tfh/units/" + type + ".txt";
//	auto	obj		= parser_UTF8::doParseFile(filename);
//	obj					= obj->getLeaves()[0];
//	name					= obj->getKey();
//
//	for (auto tokensItr: obj->safeGetTokens("usable_by"))
//	{
//		usableBy.insert(tokensItr);
//	}
//
//	string unit_type = obj->safeGetString("type");
//	if (unit_type == "air")
//	{
//		force_type = air;
//	}
//	else if (unit_type == "land")
//	{
//		force_type = land;
//	}
//	else if (unit_type == "naval")
//	{
//		force_type = navy;
//	}
//	else
//	{
//		LOG(LogLevel::Error) << "Possible bad unit type in " << filename << "!";
//	}
//
//	max_strength			= obj->safeGetInt("max_strength");
//	practicalBonus			= obj->safeGetString("on_completion");
//	practicalBonusFactor	= obj->safeGetFloat("completion_size");*/
//}
//
//
//void HoI4Regiment::output(FILE* out, int indentlevel) const
//{
//	string indents(indentlevel, '\t');
//	const char* indent = indents.c_str();
//
//	switch (type.getForceType())
//	{
//		case land:
//			fprintf(out, "%sregiment = ", indent);
//			break;
//		case navy:
//			fprintf(out, "%sship = ", indent);
//			break;
//		case air:
//			fprintf(out, "%swing = ", indent);
//			break;
//	}
//	fprintf(out, "{ ");
//	fprintf(out, "type = %s ", type.getName().c_str());
//	fprintf(out, "name = \"%s\" ", name.c_str());
//	fprintf(out, "historical_model = %d ", historicalModel);
//	fprintf(out, "}\n");
//}
//
//
//void HoI4Regiment::outputIntoProductionQueue(FILE* out) const
//{
//	fprintf(out, "\t%s = {\n", type.getName().c_str());
//	fprintf(out, "\t\tname = \"%s\"\n", name.c_str());
//	fprintf(out, "\t\thistorical_model = %d\n", historicalModel);
//	fprintf(out, "\t}\n");
//}
//
//
//HoI4RegGroup::HoI4RegGroup()
//{
//	leaderID				= 0;
//	command_level		= division;
//	productionQueue	= false;
//}
//
//
//void HoI4RegGroup::output(FILE* out, int indentlevel /* = 0*/) const
//{
//	if (isEmpty())
//	{
//		LOG(LogLevel::Warning) << "Regiment Group " << name << " has no regiments after conversion; skipping.";
//		return;
//	}
//
//	string indents(indentlevel, '\t');
//	const char* indent = indents.c_str();
//
//	switch (force_type)
//	{
//		case land:
//			switch (command_level)
//			{
//				case division:
//					fprintf(out, "%sdivision = {\n", indent);
//					break;
//				case corps:
//					fprintf(out, "%scorps = {\n", indent);
//					break;
//				case army:
//					fprintf(out, "%sarmy = {\n", indent);
//					break;
//				case armygroup:
//					fprintf(out, "%sarmygroup = {\n", indent);
//					break;
//				case theatre:
//					fprintf(out, "%stheatre = {\n", indent);
//					break;
//				default:
//					LOG(LogLevel::Error) << "Internal error: unexpected army command level!";
//			}
//			break;
//		case navy:
//			fprintf(out, "%snavy = {\n", indent);
//			break;
//		case air:
//			fprintf(out, "%sair = {\n", indent);
//			break;
//		default:
//			LOG(LogLevel::Error) << "Internal error: unexpected force type!";
//	}
//	fprintf(out, "%s\tname=\"%s\"\n", indent, name.c_str());
//	if (force_type == air || (force_type == navy && !at_sea))
//	{
//		fprintf(out, "%s\tbase = %d\n", indent, location);
//	}
//	if (leaderID)
//	{
//		fprintf(out, "%s\tleader = %d\n", indent, leaderID);
//	}
//	fprintf(out, "%s\tlocation = %d\n", indent, location);
//
//	if ((force_type == land) && (command_level == division))
//	{
//		bool reserve = false;
//		for (auto regiment : regiments)
//		{
//			if (regiment.isReserve())
//			{
//				reserve = true;
//			}
//		}
//
//		if (reserve)
//		{
//			fprintf(out, "%s\tis_reserve = yes\n", indent);
//		}
//	}
//
//	for (auto itr: regiments)
//	{
//		itr.output(out, indentlevel + 1);
//	}
//
//	for (auto itr: children)
//	{
//		itr.output(out, indentlevel + 1);
//	}
//
//	fprintf(out, "%s}\n", indent);
//}
//
//
//void HoI4RegGroup::outputIntoProductionQueue(FILE* out, const string& tag) const
//{
//	if (isEmpty())
//	{
//		LOG(LogLevel::Warning) << "Regiment Group " << name << " has no regiments after conversion; skipping.";
//		return;
//	}
//
//	if (force_type == land && command_level == division) // Build as a division
//	{
//		fprintf(out, "military_construction = {\n");
//		fprintf(out, "\tcountry = %s\n", tag.c_str());
//		fprintf(out, "\t\tname = \"%s\"\n", name.c_str());
//		for (auto itr: regiments)
//		{
//			itr.outputIntoProductionQueue(out);
//		}
//
//		fprintf(out, "\tcost = 0\n");
//		fprintf(out, "\tprogress = 0\n");
//		fprintf(out, "\tduration = 0\n"); // This makes the unit already or almost complete in the construction queue
//		fprintf(out, "}\n");
//	}
//	else
//	{
//		for (auto itr: regiments)
//		{
//			fprintf(out, "military_construction = {\n");
//			fprintf(out, "\tcountry = %s\n", tag.c_str());
//			itr.outputIntoProductionQueue(out);
//			fprintf(out, "\tcost = 0\n");
//			fprintf(out, "\tprogress = 0\n");
//			fprintf(out, "\tduration = 0\n"); // This makes the unit already or almost complete in the construction queue
//			fprintf(out, "}\n");
//		}
//	}
//
//	for (auto itr: children)
//	{
//		itr.outputIntoProductionQueue(out, tag);
//	}
//}
//
//
//HoI4RegGroup HoI4RegGroup::createChild()
//{
//	HoI4RegGroup newChild;
//	newChild.setLocation(location);
//	newChild.setForceType(force_type);
//	newChild.setAtSea(at_sea);
//	newChild.setCommandLevel((CommandLevel)(command_level - 1));
//	newChild.setName();
//	return newChild;
//}
//
//
//static int hqCount;
//void HoI4RegGroup::resetHQCounts()
//{
//	hqCount = 0;
//}
//
//
//void HoI4RegGroup::createHQs(HoI4RegimentType hqType)
//{
//	if (command_level > division)
//	{
//		HoI4Regiment hq;
//		stringstream regname;
//		regname << ++hqCount << CardinalToOrdinal(hqCount) << " Headquarters Brigade";
//		hq.setName(regname.str());
//		hq.setType(hqType);
//		hq.setHistoricalModel(0);
//		regiments.push_back(hq);
//
//		for (auto itr: children)
//		{
//			itr.createHQs(hqType);
//		}
//	}
//}
//
//
//static map<CommandLevel, int> regGroupNameCounts;
//void HoI4RegGroup::resetRegGroupNameCounts()
//{
//	for (int i = 0; i < theatre; ++i)
//	{
//		regGroupNameCounts[static_cast<CommandLevel>(i)] = 0;
//	}
//}
//
//
//void HoI4RegGroup::setName()
//{
//	if (name != "")
//	{
//		LOG(LogLevel::Warning) << "resetting name for " << name << "!";
//		}
//
//	int index = ++regGroupNameCounts[command_level];
//	stringstream newname;
//	newname << index << CardinalToOrdinal(index) << " ";
//	switch (command_level)
//	{
//		case division:
//			newname << "Division";
//			break;
//		case corps:
//			newname << "Corps";
//			break;
//		case army:
//			newname << "Army";
//			break;
//		case armygroup:
//			newname << "Army Group";
//			break;
//	}
//	name = newname.str();
//}
//
//
//bool HoI4RegGroup::addChild(HoI4RegGroup newChild, bool allowPromote)
//{
//	if ((allowPromote) && (command_level <= newChild.getCommandLevel()))
//	{
//		command_level = static_cast<CommandLevel>(newChild.getCommandLevel() + 1);
//	}
//	else if (command_level <= newChild.getCommandLevel())
//	{
//		return false;
//	}
//
//	// Am I one command level above the child and don't have too many children?
//	if ((children.size() < 5) && (command_level == (newChild.getCommandLevel() + 1)))
//	{
//		children.push_back(newChild);
//		return true;
//	}
//
//	// can an existing child take this?
//	for (auto child: children)
//	{
//		if (child.addChild(newChild, false))
//		{
//			return true;
//		}
//	}
//
//	// can I create a new child (<5 current children, or I am an armygroup)?
//	if (children.size() < 5 || command_level == armygroup)
//	{
//		// add child
//		HoI4RegGroup newerChild = createChild();
//		if (newerChild.addChild(newChild, false))
//		{
//			children.push_back(newerChild);
//			return true;
//		}
//	}
//
//	// can't add this group; can I promote myself?
//	if (allowPromote)
//	{
//		command_level = static_cast<CommandLevel>(command_level + 1);
//
//		// split current children between two new intermediate children if appropriate
//		HoI4RegGroup child1 = createChild();
//		HoI4RegGroup child2 = createChild();
//		if (command_level > corps) // original command level was higher than division
//		{
//			for (size_t i = 0; i < children.size(); ++i)
//			{
//				if (i % 2 == 0)
//				{
//					child1.children.push_back(children[i]);
//				}
//				else
//				{
//					child2.children.push_back(children[i]);
//				}
//			}
//			children.clear();
//		}
//		else // NEW command_level == corps (originally a division)
//		{
//			for (size_t i = 0; i < regiments.size(); ++i)
//			{
//				child1.regiments.push_back(regiments[i]);
//			}
//			regiments.clear();
//		}
//		children.push_back(child1);
//		if (!child2.isEmpty())
//		{
//			children.push_back(child2);
//		}
//
//		// try again: can an existing child take this?
//		for (auto itr: children)
//		{
//			if (itr.addChild(newChild, false))
//			{
//				return true;
//			}
//		}
//
//		// try again: can I create a new child (<5 current children, or I am an armygroup)?
//		if (children.size() < 5 || command_level == armygroup)
//		{
//			// add child
//			HoI4RegGroup newerChild = createChild();
//			if (newerChild.addChild(newChild, false))
//			{
//				children.push_back(newerChild);
//				return true;
//			}
//		}
//	}
//
//	children.push_back(newChild);
//	return false;
//}
//
//
//bool HoI4RegGroup::addRegiment(HoI4Regiment reg, bool allowPromote)
//{
//	// only add ships to navies and regiments to armies
//	if (force_type != reg.getForceType())
//	{
//		LOG(LogLevel::Error) << "attempted to add unit to parent of incorrect type!";
//		return false;
//	}
//
//	// build hierarchies only for land
//	if (force_type == air || force_type == navy)
//	{
//		regiments.push_back(reg);
//		return true;
//	}
//
//	// only divisions can have non-HQ regiments
//	// only non-divisions can have RegGroup children
//	if (command_level > division)
//	{
//		// can an existing child take this?
//		for (auto itr: children)
//		{
//			if (itr.addRegiment(reg, false))
//			{
//				return true;
//			}
//		}
//		// no: can I create a new child (<5 current children, or I am an armygroup)?
//		if (children.size() < 5 || command_level == armygroup)
//		{
//			// add child
//			HoI4RegGroup newChild = createChild();
//
//			// rebalance grandchildren: give the new child one grandchild from every existing child
//			if (command_level > corps)
//			{
//				for (auto itr = children.begin(); itr != children.end(); ++itr)
//				{
//					vector<HoI4RegGroup>::iterator grandchild = --itr->children.end();
//					HoI4RegGroup temp = *(grandchild);
//					itr->children.erase(grandchild);
//					newChild.children.push_back(temp);
//
//					// don't allow more than 4 grandchildren to be transferred (only a problem if I am an armygroup)
//					if (newChild.children.size() >= 4)
//					{
//						break;
//					}
//				}
//			}
//			children.push_back(newChild);
//
//			// try again: can an existing child take this?
//			for (auto itr: children)
//			{
//				if (itr.addRegiment(reg, false))
//				{
//					return true;
//				}
//			}
//		}
//	}
//	else
//	{
//		if (regiments.size() < 4)
//		{
//			regiments.push_back(reg);
//			return true;
//		}
//	}
//
//	// can't add this regiment; can I promote myself?
//	if (allowPromote)
//	{
//		// only promote up to army group
//		if (command_level < armygroup)
//		{
//			command_level = CommandLevel((int)command_level + 1);
//		}
//		else
//		{
//			LOG(LogLevel::Error) << "Internal error : tried to promote an army group!";
//			return false; // should never get here
//		}
//
//		// split current children between two new intermediate children
//		HoI4RegGroup child1 = createChild();
//		HoI4RegGroup child2 = createChild();
//		if (command_level > corps) // original command level was higher than division
//		{
//			for (size_t i = 0; i < children.size(); ++i)
//			{
//				if (i % 2 == 0)
//				{
//					child1.children.push_back(children[i]);
//				}
//				else
//				{
//					child2.children.push_back(children[i]);
//				}
//			}
//			children.clear();
//		}
//		else // NEW command_level == corps (originally a division)
//		{
//			for (size_t i = 0; i < regiments.size(); ++i)
//			{
//				if (i % 2 == 0)
//				{
//					child1.regiments.push_back(regiments[i]);
//				}
//				else
//				{
//					child2.regiments.push_back(regiments[i]);
//				}
//			}
//			regiments.clear();
//		}
//		children.push_back(child1);
//		children.push_back(child2);
//
//		// try again: can an existing child take this?
//		for (auto itr: children)
//		{
//			if (itr.addRegiment(reg, false))
//			{
//				return true;
//			}
//		}
//	}
//
//	// nope, really can't add it
//	return false;
//}
//
//
//int HoI4RegGroup::size() const 
//{
//	unsigned size = regiments.size();
//
//	for (auto itr: children)
//	{
//		size += itr.size();
//	}
//
//	return size;
//}
//
//
//void HoI4RegGroup::undoPracticalAddition(map<string, double>& practicals) const
//{
//	for (auto itr: regiments)
//	{
//		practicals[itr.getType().getPracticalBonus()] -= itr.getType().getPracticalBonusFactor();
//	}
//
//	for (auto itr: children)
//	{
//		itr.undoPracticalAddition(practicals);
//	}
//}


HoI4RegimentType::HoI4RegimentType(const string& _type, int _x, int _y):
	type(_type),
	x(_x),
	y(_y)
{
}


ostream& operator << (ostream& out, const HoI4RegimentType& regiment)
{
	out << "\t\t" << regiment.type << " = { x = " << regiment.x << " y = " << regiment.y << " }\n";

	return out;
}


HoI4DivisionTemplateType::HoI4DivisionTemplateType(const string& _name):
	name(_name),
	regiments(),
	supportRegiments()
{
}


ostream& operator << (ostream& out, const HoI4DivisionTemplateType& rhs)
{
	out << "division_template = {\n";
	out << "\tname = \"" << rhs.name << "\"\n";
	out << endl;
	out << "\tregiments = {\n";
	for (auto regiment: rhs.regiments)
	{
		out << regiment;
	}
	out << "\t}\n";
	out << "\tsupport = {\n";
	for (auto regiment: rhs.supportRegiments)
	{
		out << regiment;
	}
	out << "\t}\n";
	out << "}\n";

	return out;
}


HoI4DivisionType::HoI4DivisionType(const string& _name, const string& _type, int _location):
	name(_name),
	type(_type),
	location(_location)
{
}


ostream& operator << (ostream& out, const HoI4DivisionType& division)
{
	out << "\tdivision = {\n";
	out << "\t\tname = \"" << division.name << "\"\n";
	out << "\t\tlocation = " << division.location << "\n";
	out << "\t\tdivision_template = \"" << division.type << "\"\n";
	out << "\t\tstart_experience_factor = 0.3\n";
	out << "\t}\n";

	return out;
}

HoI4UnitMap::HoI4UnitMap(const string& _category, const string& _type, const string& _equipment, int _size):
	category(_category),
	type(_type),
	equipment(_equipment),
	size(_size)
{
}

HoI4UnitMap::HoI4UnitMap():
	category(""),
	type(""),
	equipment(""),
	size(0)
{
}

string HoI4UnitMap::getCategory()
{
	return category;
}

string HoI4UnitMap::getType()
{
	return type;
}

string HoI4UnitMap::getEquipment()
{
	return equipment;
}

int HoI4UnitMap::getSize()
{
	return size;
}

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



#ifndef COLONIAL_TAG_MAPPER_H
#define COLONIAL_TAG_MAPPER_H



#include "newParser.h"
#include <string>
#include <vector>



namespace mappers
{
	typedef struct
	{
		std::string tag;
		std::string EU4Region;
		std::string V2Region;
		std::string cultureGroup;
	} colonyStruct;


	class colonialTagMapper: commonItems::parser
	{
		public:
			static const std::vector<colonyStruct>& getColonyMap()
			{
				return getInstance()->colonyMap;
			}

		private:
			static colonialTagMapper* instance;
			static colonialTagMapper* getInstance()
			{
				if (instance == nullptr)
				{
					instance = new colonialTagMapper;
				}
				return instance;
			}

			colonialTagMapper();
			void initMapping(const std::string& unused, std::istream& theStream);

			std::vector<colonyStruct> colonyMap;
	};
}



#endif // COLONIAL_TAG_MAPPER_H

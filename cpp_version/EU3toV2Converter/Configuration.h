#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include "Date.h"

using namespace std;

class Configuration // Singleton
{
public:
	Configuration();

	static date getStartDate()
	{
		return getInstance()->startDate;
	}

	static string getV2Path()
	{
		return getInstance()->V2Path;
	}

	static string getEU3Path()
	{
		return getInstance()->EU3Path;
	}

	static string getGametype()
	{
		return getInstance()->gametype;
	}

	static Configuration* getInstance()
	{
		if (instance == NULL)
			instance = new Configuration();
		return instance;
	}

private:
	static Configuration* instance;

	date startDate;
	string V2Path;
	string EU3Path;
	string gametype;
};

#endif // CONFIGURATION_H_
#ifndef REPOSITORIES_DATASYNK_H
#define REPOSITORIES_DATASYNK_H

#include "../../../../Infrastructure/Config/domainConfig.h"

class DataSyncUseCase
{
public:
	static bool synkFromLocal();
	static bool synkFromRemote();

	static bool setData(const string& serialized);
	static string getData();
};

#endif
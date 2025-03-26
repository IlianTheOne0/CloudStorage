#ifndef REPOSITORIES_DATASYNK_H
#define REPOSITORIES_DATASYNK_H

class DataSyncRepository
{
public:
	static bool synkFromRemote();
	static bool synkFromLocal();
};

#endif
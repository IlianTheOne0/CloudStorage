#ifndef REPOSITORIES_DATASYNK_H
#define REPOSITORIES_DATASYNK_H

class DataSyncRepository
{
public:
	static bool synkFromLocal();
	static bool synkFromRemote();
};

#endif
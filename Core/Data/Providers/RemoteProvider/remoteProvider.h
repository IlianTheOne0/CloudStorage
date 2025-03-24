#ifndef PROVIDERS_REMOTE_H
#define PROVIDERS_REMOTE_H

#include "../Base/AProviders.h"

class RemoteProvider
	: AProviders
{
private:
	string _path;
public:
	RemoteProvider();
	~RemoteProvider() override = default;

	bool save(const string& data) override;
	string load() override;
};

#endif
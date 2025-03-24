#ifndef PROVIDERS_LOCAL_H
#define PROVIDERS_LOCAL_H

#include "../Base/AProviders.h"

class LocalProvider
	: AProviders
{
private:
	string _path;
public:
	LocalProvider();
	~LocalProvider() override = default;

	bool save(const string& data) override;
	string load() override;
};

#endif
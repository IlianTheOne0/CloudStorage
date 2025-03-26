#ifndef PROVIDERS_REMOTE_H
#define PROVIDERS_REMOTE_H

#include "../Base/AProviders.h"
#include "../../../Domain/domain.h"

class RemoteProvider
	: public AProviders
{
private:
	string _path;
public:
	RemoteProvider();
	~RemoteProvider() override = default;

	string load() const override;
	bool save(const string& data) override;
};

#endif
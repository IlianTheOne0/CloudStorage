#ifndef PROVIDERS_LOCAL_H
#define PROVIDERS_LOCAL_H

#include "../Base/AProviders.h"
#include "../../../Domain/domain.h"

class LocalProvider
	: public AProviders
{
private:
	string _path;
public:
	LocalProvider();
	~LocalProvider() override = default;

	string load() const override;
	bool save(const string& data) override;
};

#endif
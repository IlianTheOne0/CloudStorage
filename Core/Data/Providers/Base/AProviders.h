#ifndef PROVIDERS_ABSTRACTION_H
#define PROVIDERS_ABSTRACTION_H

#include "IProviders.h"

#include "../../../Domain/domain.h"

class AProviders
	: public IProviders
{
private:
	shared_ptr<string> load_(const string& path) override;
	bool save_(const string& path, const string& data) override;
public:
	AProviders() = default;
	~AProviders() override = default;

	virtual bool save(const string& data) = 0;
	virtual shared_ptr<string> load() = 0;
};

#endif
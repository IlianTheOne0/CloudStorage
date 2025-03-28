#ifndef PROVIDERS_ABSTRACTION_H
#define PROVIDERS_ABSTRACTION_H

#include "../../../Domain/domain.h"

class AProviders abstract
	: public ProvidersRepository
{
protected:
	string load_(const string& path) const;
	bool save_(const string& path, const string& data);
public:
	AProviders() = default;
	~AProviders() override = default;
};

#endif
#ifndef PROVIDERS_INTERFACE_H
#define PROVIDERS_INTERFACE_H

#include "../../../../Infrastructure/Config/dataConfig.h"

class ProvidersRepository
{
public:
	virtual ~ProvidersRepository() = default;

	virtual string load() const = 0;
	virtual bool save(const string& data) = 0;
};

#endif
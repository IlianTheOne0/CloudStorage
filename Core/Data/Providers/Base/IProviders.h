#ifndef PROVIDERS_INTERFACE_H
#define PROVIDERS_INTERFACE_H

#include "../../../../Infrastructure/Config/dataConfig.h"

class IProviders
{
protected:
	virtual string load_(const string& path) const = 0;
	virtual bool save_(const string& path, const string& data) = 0;
public:
	virtual ~IProviders() = default;
};

#endif
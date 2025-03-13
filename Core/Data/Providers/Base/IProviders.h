#ifndef PROVIDERS_INTERFACE_H
#define PROVIDERS_INTERFACE_H

#include "../../../../Utils/dataConfig.h"

class IProviders
{
protected:
	virtual bool save_(const string& path, const string& data) = 0;
	virtual shared_ptr<string> load_(const string& path) = 0;
public:
	virtual ~IProviders() = default;
};

#endif
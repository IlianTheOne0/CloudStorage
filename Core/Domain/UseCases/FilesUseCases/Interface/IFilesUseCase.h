#ifndef FILES_INTERFACE_H
#define FILES_INTERFACE_H

#include "../../../../../Infrastructure/Config/domainConfig.h"

class IFilesUseCase
{
public:
	virtual ~IFilesUseCase() = default;

	virtual void edit(const string& value) = 0;
};

#endif
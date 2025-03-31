#ifndef DOMAIN_RESPONSE_H
#define DOMAIN_RESPONSE_H

#include "headerTypeEnum.h"
#include "../../../../Infrastructure/Config/domainConfig.h"

struct DomainResponse
{
	HeaderTypes header;
	wstring body;
};

#endif
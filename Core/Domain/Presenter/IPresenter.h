#ifndef PRESENTER_INTERFACE_H
#define PRESENTER_INTERFACE_H

#include "../Entities/DomainResponse/domainResponse.h"
#include "../Entities/DomainResponse/headerTypeEnum.h"
#include "../../Presentation/presentation.h"
#include "../../../Infrastructure/Config/domainConfig.h"

class IPresenter
{
public:
	virtual ~IPresenter() = default;

	virtual ViewModel handle(const wstring& input) = 0;
};

#endif

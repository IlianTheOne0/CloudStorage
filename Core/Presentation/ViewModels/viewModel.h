#ifndef VIEW_MODEL_H
#define VIEW_MODEL_H

#include "../../Domain/Entities/DomainResponse/headerTypeEnum.h"
#include "../../../Infrastructure/Config/presentationConfig.h"

struct ViewModel
{
	HeaderTypes title;
	wstring message;
};

#endif
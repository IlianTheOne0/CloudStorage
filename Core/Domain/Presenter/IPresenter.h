#ifndef PRESENTER_INTERFACE_H
#define PRESENTER_INTERFACE_H

#include "../Entites/entites.h"

class IPresenter
{
public:
	virtual ~IPresenter() = default;

	virtual void present(const DomainResponse& response) = 0;
};

#endif
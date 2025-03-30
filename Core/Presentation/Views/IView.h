#ifndef VIEWS_INTERFACE_H
#define VIEWS_INTERFACE_H

#include "../ViewModels/viewModel.h"

class IView
{
public:
	virtual ~IView() = default;
	
	virtual void display(const ViewModel& viewModel) = 0;
};

#endif
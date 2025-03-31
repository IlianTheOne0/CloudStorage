#ifndef PRESENTER_H
#define PRESENTER_H

#include "IPresenter.h"
#include "../../Presentation/presentation.h"

class Presenter
	: public IPresenter
{
public:
	Presenter() = default;
	~Presenter() override = default;

	ViewModel handle(const wstring& input) override;
};

#endif
#ifndef PRESENTER_H
#define PRESENTER_H

#include "IPresenter.h"
#include "../../Presentation/presentation.h"

class Presenter
	: public IPresenter
{
private:
	IView* _view;
public:
	Presenter(IView* view);
	~Presenter() override = default;

	void present(const DomainResponse& response) override;
};

#endif
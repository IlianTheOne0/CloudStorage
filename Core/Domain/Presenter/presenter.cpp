#include "presenter.h"
#include "../../../Infrastructure/Config/domainConfig.h"

Presenter::Presenter(IView* view)
	: _view(view)
{ }

void Presenter::present(const DomainResponse& response)
{
	ViewModel viewModel;

	viewModel.title = response.header;
	viewModel.message = response.body;

	_view->display(viewModel);
}
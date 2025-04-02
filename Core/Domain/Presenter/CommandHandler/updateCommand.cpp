#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::updateCommand(vector<wstring> tokens)
{
	if (tokens.size() != 1) { return { HeaderTypes::ErrorType, L"Usage: update" }; }

	return { HeaderTypes::UpdateType, L"" };
}
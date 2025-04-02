#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::exitCommand(vector<wstring> tokens)
{
    if (tokens.size() != 1) { return { HeaderTypes::ErrorType, L"Usage: exit" }; }
    Screen::Updater::setExitFlag(true);
    return { HeaderTypes::SuccessfulType, L"Exiting the program..." };
}
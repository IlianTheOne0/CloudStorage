#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::renameCommand(vector<wstring> tokens, const bool& consoleShowHidden)
{
    if (tokens.size() < 3) { return { HeaderTypes::ErrorType, L"Usage: rename <old name> <new name>" }; }

    shared_ptr<Directory> root = Screen::Updater::getData();
    vector<shared_ptr<Unit>>::iterator it = Tools::find(root, Tools::wstringToString(tokens[1]));

    if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

    shared_ptr<Unit> unit = *it;

    if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }
    if (Tools::find(root, Tools::wstringToString(tokens[2])) != root->getContents().end()) { return { HeaderTypes::ErrorType, L"The name '" + tokens[2] + L"' already exists" }; }

    unit->setName(Tools::wstringToString(tokens[2]));
    return { HeaderTypes::SuccessfulType, L"Renaming '" + tokens[1] + L"' is successful!" };
}
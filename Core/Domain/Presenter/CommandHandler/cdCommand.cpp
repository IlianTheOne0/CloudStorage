#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::cdCommand(vector<wstring> tokens, const bool& consoleShowHidden)
{
    if (tokens.size() < 2) { return { HeaderTypes::ErrorType, L"Usage: cd <name/..>" }; };

    if (tokens[1] == L"..")
    {
        shared_ptr<Directory> parent = Screen::Updater::getParentDirectory();
        if (parent) { Screen::Updater::setData(parent, false); return { HeaderTypes::SuccessfulType, L"Changed directory to parent" }; }
        return { HeaderTypes::ErrorType, L"No parent directory found" };
    }

    shared_ptr<Directory> root = Screen::Updater::getData();
    for (shared_ptr<Unit>& unit : root->getContents())
    {
        if (unit->getName() == Tools::wstringToString(tokens[1]) && unit->getFileType() == FileTypes::DirectoryType)
        {
            if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType,  L"Directory '" + tokens[1] + L"' not found" }; }

            Screen::Updater::setData(dynamic_pointer_cast<Directory>(unit));
            return { HeaderTypes::SuccessfulType, L"Changed directory to '" + tokens[1] + L"'" };
        }
    }
    return { HeaderTypes::ErrorType, L"Directory '" + tokens[1] + L"' not found" };
}
#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel changeHidden(vector<wstring> tokens, const bool& consoleShowHidden)
{
    shared_ptr<Directory> root = Screen::Updater::getData();
    vector<shared_ptr<Unit>>::iterator it = Tools::find(root, Tools::wstringToString(tokens[2]));

    if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[2] + L" not found" }; }

    shared_ptr<Unit> unit = *it;

    if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[2] + L" not found" }; }

    unit->setIsHidden(!unit->getIsHidden());
    return { HeaderTypes::SuccessfulType, L"Changed hidden state of '" + tokens[2] + L"' successfully!" };
}

ViewModel changeConfig(vector<wstring> tokens, ConfigParser& config)
{
    config.set(Tools::wstringToString(tokens[2]), Tools::wstringToString(tokens[3]));
    if (!config.save()) { return { HeaderTypes::ErrorType, L"Failed to save config file." }; }

    return { HeaderTypes::SuccessfulType, L"Config updated successfully" };
}

ViewModel Presenter::CommandHandler::changeCommand(vector<wstring> tokens, const bool& consoleShowHidden, ConfigParser& config)
{
    ViewModel result = { HeaderTypes::ErrorType, L"Usage: change [hidden|config] ..." };

    if (tokens.size() < 2) { return result; }

    if (tokens[1] == L"hidden")
    {
        if (tokens.size() < 3) { return { HeaderTypes::ErrorType, L"Usage: change hidden <name>" }; }
        return changeHidden(tokens, consoleShowHidden);
    }
    else if (tokens[1] == L"config")
    {
        if (tokens.size() < 4) { return { HeaderTypes::ErrorType, L"Usage: change config <key> <value>" }; }
        return changeConfig(tokens, config);
    }
    else { return result; }
}
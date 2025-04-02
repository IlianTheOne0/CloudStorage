#include "presenter.h"
#include "../../../Infrastructure/Config/domainConfig.h"
#include "../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::handle(const wstring& input)
{
    DomainResponse response{ HeaderTypes::ErrorType, L"'" + input + L"'" + L" is not recognized" };
    ViewModel result{ response.header, response.body };

    if (input.empty()) { return { response.header, response.body }; }
    else
    {
        vector<wstring> tokens = Tools::split(input, L' ');
        ConfigParser config(CONFIG_PATH);
        config.load();
        bool consoleShowHidden = (config.get("consoleShowHidden") == "true");

        if (tokens[0] == L"cd") { return CommandHandler::cdCommand(tokens, consoleShowHidden); }
        else if (tokens[0] == L"change") { return CommandHandler::changeCommand(tokens, consoleShowHidden, config); }
        else if (tokens[0] == L"del") { return CommandHandler::delCommand(tokens, consoleShowHidden); }
        else if (tokens[0] == L"exit") { return CommandHandler::exitCommand(tokens); }
        else if (tokens[0] == L"info") { return CommandHandler::infoCommand(tokens, consoleShowHidden); }
        else if (tokens[0] == L"mkdir") { return CommandHandler::mkdirCommand(tokens); }
        else if (tokens[0] == L"notepad") { return CommandHandler::notepadCommand(tokens); }
        else if (tokens[0] == L"open") { return CommandHandler::openCommand(tokens, consoleShowHidden); }
        else if (tokens[0] == L"rename") { return CommandHandler::renameCommand(tokens, consoleShowHidden); }
        else if (tokens[0] == L"update") { return CommandHandler::updateCommand(tokens); }
    }

    return { response.header, response.body };
}
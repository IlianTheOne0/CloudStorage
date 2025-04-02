#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::mkdirCommand(vector<wstring> tokens)
{
    if (tokens.size() < 2) { return { HeaderTypes::ErrorType, L"Usage: mkdir [-h] <name>" }; };

    bool isHidden = tokens.size() > 2 && tokens[1] == L"-h";
    wstring dirName = isHidden ? tokens[2] : tokens[1];

    shared_ptr<Directory> root = Screen::Updater::getData();
    if (Tools::find(root, Tools::wstringToString(dirName)) != root->getContents().end()) { return { HeaderTypes::ErrorType, L"Directory exists" }; }

    DirectoryUseCase::addByParams(root, Tools::wstringToString(dirName), FileTypes::DirectoryType, isHidden);
    return { HeaderTypes::SuccessfulType, L"Directory created" };
}
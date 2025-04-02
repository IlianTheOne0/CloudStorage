#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::notepadCommand(vector<wstring> tokens)
{
    if (tokens.size() < 2) { return { HeaderTypes::ErrorType, L"Usage: notepad [-h] <name>" }; };

    bool isHidden = tokens.size() > 2 && tokens[1] == L"-h";
    wstring fileName = isHidden ? tokens[2] : tokens[1];

    shared_ptr<Directory> root = Screen::Updater::getData();
    if (Tools::find(root, Tools::wstringToString(fileName)) != root->getContents().end()) { return { HeaderTypes::ErrorType, L"File exists" }; }

    DirectoryUseCase::addByParams(root, Tools::wstringToString(fileName) + ".text", FileTypes::TextFileType, isHidden);
    return { HeaderTypes::SuccessfulType, L"File created" };
}
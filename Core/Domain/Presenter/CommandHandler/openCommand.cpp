#include "../presenter.h"
#include "../../../../Infrastructure/Config/domainConfig.h"
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"

ViewModel Presenter::CommandHandler::openCommand(vector<wstring> tokens, const bool& consoleShowHidden)
{
    if (tokens.size() < 2) { return { HeaderTypes::ErrorType, L"Usage: open <name><format>" }; }

    shared_ptr<Directory> root = Screen::Updater::getData();
    vector<shared_ptr<Unit>>::iterator it = Tools::find(root, Tools::wstringToString(tokens[1]));

    if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

    shared_ptr<Unit> unit = *it;

    if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }
    if (unit->getFileType() != FileTypes::TextFileType) { return { HeaderTypes::ErrorType, L"Can only open text files" }; }

    shared_ptr<AFile> file = dynamic_pointer_cast<AFile>(unit);
    wstring fileNameW = Tools::stringToWString(file->getName());
    wstring contentW = Tools::stringToWString(file->getContent());
    if (contentW.empty()) contentW = L" ";
    wstring message = fileNameW + L"|" + contentW;

    return { HeaderTypes::FillType, message };
}
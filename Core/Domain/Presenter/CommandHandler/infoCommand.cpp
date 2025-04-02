#include "../presenter.h"  
#include "../../../../Infrastructure/Config/domainConfig.h"  
#include "../../UseCases/DirectoryUseCase/directoryUseCase.h"  

ViewModel Presenter::CommandHandler::infoCommand(vector<wstring> tokens, const bool& consoleShowHidden)
{
    shared_ptr<Directory> root = Screen::Updater::getData();

    if (tokens.size() > 2) { return { HeaderTypes::ErrorType, L"Usage: info <[nothing]/name>" }; }
    else if (tokens.size() == 1)
    {
        wstring properties =
            L"Name: " + Tools::stringToWString(root->getName()) + L"|" +
            L"Is hidden: " + (root->getIsHidden() ? L"yes" : L"no") + L"|" +
            L"Created date: " + L"|    " + Tools::stringToWString(Tools::timeToString(root->getCreatedDate())) + L"|" +
            L"Last edited date: " + L"|    " + Tools::stringToWString(Tools::timeToString(root->getLastEditedDate())) + L"|" +
            L"File type: Directory";

        return { HeaderTypes::PropType, properties };
    }
    else
    {
        vector<shared_ptr<Unit>>::iterator it = Tools::find(root, Tools::wstringToString(tokens[1]));

        if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

        shared_ptr<Unit> unit = *it;

        if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

        wstring fileTypeStr;
        switch (unit->getFileType())
        {
            case FileTypes::TextFileType: { fileTypeStr = L"Text File"; } break;
            case FileTypes::DirectoryType: { fileTypeStr = L"Directory"; } break;
            default: { fileTypeStr = L"Unknown"; } break;
        }

        wstring properties =
            L"Name: " + Tools::stringToWString(unit->getName()) + L"|" +
            L"Is hidden: " + (unit->getIsHidden() ? L"yes" : L"no") + L"|" +
            L"Created date: " + L"|    " + Tools::stringToWString(Tools::timeToString(unit->getCreatedDate())) + L"|" +
            L"Last edited date: " + L"|    " + Tools::stringToWString(Tools::timeToString(unit->getLastEditedDate())) + L"|" +
            L"File type: " + fileTypeStr;

        return { HeaderTypes::PropType, properties };
    }
}
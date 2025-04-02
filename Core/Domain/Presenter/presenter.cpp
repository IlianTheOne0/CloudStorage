#include "presenter.h"
#include "../../../Infrastructure/Config/domainConfig.h"
#include "../UseCases/DirectoryUseCase/directoryUseCase.h"

string timeToString(const time_t& time)
{
    tm tm_struct;
    localtime_s(&tm_struct, &time);
    ostringstream oss;
    oss << put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

ViewModel Presenter::handle(const wstring& input)
{
    DomainResponse response{ HeaderTypes::ErrorType, L"'" + input + L"'" + L" is not recognized" };
    ViewModel result{ response.header, response.body };

    if (input.empty()) return { response.header, response.body };
    else
    {
        vector<wstring> tokens = ConsoleView::split(input, L' ');
        ConfigParser config(CONFIG_PATH);
        config.load();

        if (tokens[0] == L"exit")
        {
            Screen::Updater::setExitFlag(true);
            return { HeaderTypes::SuccessfulType, L"Exiting the program..." };
        }
        else if (tokens[0] == L"mkdir")
        {

            if (tokens.size() < 2) { return result; };

            bool isHidden = tokens.size() > 2 && tokens[1] == L"-h";
            wstring dirName = isHidden ? tokens[2] : tokens[1];

            shared_ptr<Directory> root = Screen::Updater::getData();
            if (any_of(root->getContents().begin(), root->getContents().end(), [&](shared_ptr<Unit>& unit) { return unit->getName() == ConsoleView::wstringToString(dirName); }))
            { return { HeaderTypes::ErrorType, L"Directory exists" }; }

            DirectoryUseCase::addByParams(root, ConsoleView::wstringToString(dirName), FileTypes::DirectoryType, isHidden);
            return { HeaderTypes::SuccessfulType, L"Directory created" };
        }
        else if (tokens[0] == L"notepad")
        {
            if (tokens.size() < 2) { return result; };

            bool isHidden = tokens.size() > 2 && tokens[1] == L"-h";
            wstring fileName = isHidden ? tokens[2] : tokens[1];

            shared_ptr<Directory> root = Screen::Updater::getData();
            if (any_of(root->getContents().begin(), root->getContents().end(), [&](shared_ptr<Unit>& unit) { return unit->getName() == ConsoleView::wstringToString(fileName); }))
            { return { HeaderTypes::ErrorType, L"File exists" }; }

            DirectoryUseCase::addByParams(root, ConsoleView::wstringToString(fileName) + ".text", FileTypes::TextFileType, isHidden);
            return { HeaderTypes::SuccessfulType, L"File created" };
        }
        else if (tokens[0] == L"cd")
        {
            if (tokens.size() < 2) { return result; };

            ConfigParser config(CONFIG_PATH);
            if (!config.load()) { throw runtime_error("Cannot load the config"); }
            bool consoleShowHidden = (config.get("consoleShowHidden") == "true");

            if (tokens[1] == L"..")
            {
                if (auto parent = Screen::Updater::getParentDirectory()) { Screen::Updater::setData(parent, false); return { HeaderTypes::SuccessfulType, L"Changed directory to parent" }; }
                return { HeaderTypes::ErrorType, L"No parent directory found" };
            }

            auto root = Screen::Updater::getData();
            for (auto& unit : root->getContents())
            {
                if (unit->getName() == ConsoleView::wstringToString(tokens[1]) && unit->getFileType() == FileTypes::DirectoryType)
                {
                    if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType,  L"Directory '" + tokens[1] + L"' not found" }; }

                    Screen::Updater::setData(dynamic_pointer_cast<Directory>(unit));
                    return { HeaderTypes::SuccessfulType, L"Changed directory to '" + tokens[1] + L"'" };
                }
            }
            return { HeaderTypes::ErrorType, L"Directory '" + tokens[1] + L"' not found"};
        }
        else if (tokens[0] == L"del")
        {
            if (tokens.size() < 2) { return result; };

            wstring targetName = tokens[1];
            shared_ptr<Directory> root = Screen::Updater::getData();
            auto it = find_if(root->getContents().begin(), root->getContents().end(), [&](auto& u) { return u->getName() == ConsoleView::wstringToString(targetName); });

            if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

            auto unit = *it;
            bool consoleShowHidden = (config.get("consoleShowHidden") == "true");

            if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

            DirectoryUseCase::remove(root, ConsoleView::wstringToString(targetName));
            return { HeaderTypes::SuccessfulType, tokens[1] + L" deleted" };
        }
        else if (tokens[0] == L"info")
        {
            shared_ptr<Directory> root = Screen::Updater::getData();
            bool consoleShowHidden = (config.get("consoleShowHidden") == "true");

            if (tokens.size() == 1)
            {
                wstring properties =
                    L"Name: " + ConsoleView::toWString(root->getName()) + L"|" +
                    L"Is hidden: " + (root->getIsHidden() ? L"true" : L"false") + L"|" +
                    L"Created date: " + L"|    " + ConsoleView::toWString(timeToString(root->getCreatedDate())) + L"|" +
                    L"Last edited date: " + L"|    " + ConsoleView::toWString(timeToString(root->getLastEditedDate())) + L"|" +
                    L"File type: Directory";

                return { HeaderTypes::PropType, properties };
            }
            else if (tokens.size() == 2)
            {
                wstring targetName = tokens[1];
                vector<shared_ptr<Unit>>::iterator it = find_if(root->getContents().begin(), root->getContents().end(), [&](shared_ptr<Unit>& unit) { return unit->getName() == ConsoleView::wstringToString(targetName); });

                if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, targetName + L" not found" }; }

                shared_ptr<Unit> unit = *it;

                if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, targetName + L" not found" }; }

                wstring fileTypeStr;
                switch (unit->getFileType())
                {
                    case FileTypes::TextFileType: { fileTypeStr = L"Text File"; } break;
                    case FileTypes::DirectoryType: {fileTypeStr = L"Directory"; } break;
                    default: fileTypeStr = L"Unknown"; break;
                }

                wstring properties =
                    L"Name: " + ConsoleView::toWString(unit->getName()) + L"|" +
                    L"Is hidden: " + (unit->getIsHidden() ? L"true" : L"false") + L"|" +
                    L"Created date: " + L"|    " + ConsoleView::toWString(timeToString(unit->getCreatedDate())) + L"|" +
                    L"Last edited date: " + L"|    " + ConsoleView::toWString(timeToString(unit->getLastEditedDate())) + L"|" +
                    L"File type: " + fileTypeStr;

                return { HeaderTypes::PropType, properties };
            }

            return result;
        }
        else if (tokens[0] == L"open")
        {
            if (tokens.size() < 2) { return result; }

            wstring targetName = tokens[1];
            shared_ptr<Directory> root = Screen::Updater::getData();
            vector<shared_ptr<Unit>>::iterator it = find_if(root->getContents().begin(), root->getContents().end(), [&](shared_ptr<Unit>& unit) { return unit->getName() == ConsoleView::wstringToString(targetName); });

            if (it == root->getContents().end()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }

            shared_ptr<Unit> unit = *it;
            bool consoleShowHidden = (config.get("consoleShowHidden") == "true");

            if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType, tokens[1] + L" not found" }; }
            if (unit->getFileType() != FileTypes::TextFileType) { return { HeaderTypes::ErrorType, L"Can only open text files" }; }

            shared_ptr<AFile> file = dynamic_pointer_cast<AFile>(unit);
            wstring fileNameW = ConsoleView::toWString(file->getName());
            wstring contentW = ConsoleView::toWString(file->getContent());
            if (contentW.empty()) contentW = L" ";
            wstring message = fileNameW + L"|" + contentW;

            return { HeaderTypes::FillType, message };
        }
    }

    return { response.header, response.body };
}
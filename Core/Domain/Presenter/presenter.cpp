#include "presenter.h"
#include "../../../Infrastructure/Config/domainConfig.h"
#include "../UseCases/DirectoryUseCase/directoryUseCase.h"

vector<wstring> split(const wstring& input, wchar_t delimiter)
{
    vector<wstring> tokens;
    wstringstream stream(input);
    wstring token;

    while (getline(stream, token, delimiter)) { tokens.push_back(token); }

    return tokens;
}

string wstringToString(const wstring& wstr) { return string(wstr.begin(), wstr.end()); }

ViewModel Presenter::handle(const wstring& input)
{
    DomainResponse response{ HeaderTypes::ErrorType, L"'" + input + L"'" + L" is not recognized" };
    ViewModel result{ response.header, response.body };

    if (input.empty()) return { response.header, response.body };
    else
    {
        vector<wstring> tokens = split(input, L' ');
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
            if (any_of(root->getContents().begin(), root->getContents().end(), [&](auto& u) { return u->getName() == wstringToString(dirName); }))
            { return { HeaderTypes::ErrorType, L"Directory exists" }; }

            DirectoryUseCase::addByParams(root, wstringToString(dirName), FileTypes::DirectoryType, isHidden);
            return { HeaderTypes::SuccessfulType, L"Directory created" };
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
                if (unit->getName() == wstringToString(tokens[1]) && unit->getFileType() == FileTypes::DirectoryType)
                {
                    if (!consoleShowHidden && unit->getIsHidden()) { return { HeaderTypes::ErrorType,  L"Directory '" + tokens[1] + L"' not found" }; }

                    Screen::Updater::setData(dynamic_pointer_cast<Directory>(unit));
                    return { HeaderTypes::SuccessfulType, L"Changed directory to '" + tokens[1] + L"'" };
                }
            }
            return { HeaderTypes::ErrorType, L"Directory '" + tokens[1] + L"' not found"};
        }
    }

    return { response.header, response.body };
}
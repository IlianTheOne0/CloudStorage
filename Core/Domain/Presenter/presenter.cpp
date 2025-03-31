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

    if (input.empty()) { return result; }
    else
    {
        vector<wstring> tokens = split(input, L' ');

        if (tokens[0] == L"exit")
        {
            Screen::Updater::setExitFlag(true);
            response = { HeaderTypes::SuccessfulType, L"Exiting the program..." };
            result = { response.header, response.body };
            return result;
        }
        else if (tokens[0] == L"mkdir")
        {
            bool isHidden = false;
            if (tokens.size() > 2 && tokens[1].find(L"-h") == 0) { isHidden = true; }
            if (tokens.size() > 3) { return result; }

            wstring dirName = isHidden ? tokens[2] : tokens[1];
            shared_ptr<Directory> rootDirectory = Screen::Updater::getData();
            if (!rootDirectory) { rootDirectory = make_shared<Directory>("root", isHidden); }

            for (const auto& unit : rootDirectory->getContents())
            {
                if (unit->getName() == wstringToString(dirName))
                {
                    response = { HeaderTypes::ErrorType, L"'" + dirName + L"' already exists" };
                    result = { response.header, response.body };
                    return result;
                }
            }

            DirectoryUseCase::addByParams(rootDirectory, wstringToString(dirName), FileTypes::DirectoryType, isHidden);

            response = { HeaderTypes::SuccessfulType, L"'" + dirName + L"' created successfully" };
            result = { response.header, response.body };

            Screen::Updater::setData(rootDirectory);
        }
    }

    result.title = response.header; result.message = response.body;
    return result;
}

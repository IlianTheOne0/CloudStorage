#include "../tools.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"

vector<wstring> Tools::split(const wstring& input, wchar_t delimiter)
{
    vector<wstring> tokens;
    wstringstream stream(input);
    wstring token;

    while (getline(stream, token, delimiter)) { tokens.push_back(token); }

    return tokens;
}
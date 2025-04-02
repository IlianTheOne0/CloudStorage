#include "../tools.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"

wstring Tools::stringToWString(const string& str)
{
    size_t size;
    mbstowcs_s(&size, nullptr, 0, str.c_str(), 0);
    vector<wchar_t> buffer(size);
    mbstowcs_s(&size, buffer.data(), size, str.c_str(), size - 1);

    return wstring(buffer.data());
}
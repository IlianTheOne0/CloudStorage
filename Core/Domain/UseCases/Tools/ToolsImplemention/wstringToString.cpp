#include "../tools.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"

string Tools::wstringToString(const wstring& wstr) { return string(wstr.begin(), wstr.end()); }
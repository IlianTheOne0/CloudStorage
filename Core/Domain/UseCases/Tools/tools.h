#ifndef TOOLS_USECASES_H
#define TOOLS_USECASES_H

#include "../../Entities/entities.h"

class Tools
{
public:
	static vector<wstring> split(const wstring& input, wchar_t delimiter);
	static vector<shared_ptr<Unit>>::iterator find(const shared_ptr<Directory>& root, const string& targetName);
	static wstring stringToWString(const string& str);
	static string timeToString(const time_t& time);
	static string wstringToString(const wstring& wstr);
};

#endif
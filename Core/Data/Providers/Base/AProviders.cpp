#include "AProviders.h"

string AProviders::load_(const string& path)
{
    fstream file(path);

    if (canonical(path) != path) { ERROR("class AProviders -> method load_: The path is incorrect!"); throw invalid_argument("The path is incorrect!"); }
    if (!exists(path)) { ERROR("class AProviders -> method load_: File does not exist at path!"); throw runtime_error("File does not exist at path!"); }
    if (!file.is_open()) { ERROR("class AProviders -> method load_: Unable to open file at path!"); throw runtime_error("Unable to open file at path!"); }

	string read, result;
	while (getline(file, read))
	{
		if (read.empty()) { continue; }
		result += read;
	}

	INFO("class AProviders -> method load_: The operation was completed successfully!;");
	return result;
}

bool AProviders::save_(const string& path, const string& data)
{
	ofstream file(path);

	if (canonical(path) != path) { ERROR("class AProviders -> method save_: The path is incorrect!"); throw invalid_argument("The path is incorrect!"); }
	if (!exists(path)) { ERROR("class AProviders -> method save_: File does not exist at path!"); throw runtime_error("File does not exist at path!"); }
	if (!file.is_open()) { ERROR("class AProviders -> method save_: Unable to open file at path!"); throw runtime_error("Unable to open file at path!"); }

	file << data;

	INFO("class AProviders -> method save_: The operation was completed successfully!;");
	return true;
}
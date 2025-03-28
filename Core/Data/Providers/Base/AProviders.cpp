#include "AProviders.h"

string AProviders::load_(const string& path) const
{
    ifstream file(path, ios::binary);

    if (canonical(path) != path) { ERROR("class AProviders -> method load_: The path is incorrect!"); 
    
    invalid_argument("The path is incorrect!"); }
    if (!exists(path)) { ERROR("class AProviders -> method load_: File does not exist at path!"); throw runtime_error("File does not exist at path!"); }
    if (!file.is_open()) { ERROR("class AProviders -> method load_: Unable to open file at path!"); throw runtime_error("Unable to open file at path!"); }

    string result((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    INFO("class AProviders -> method load_: The operation was completed successfully!;");
    return result;
}

bool AProviders::save_(const string& path, const string& data)
{
    ofstream file(path, ios::binary);

    if (canonical(path) != path) { ERROR("class AProviders -> method save_: The path is incorrect!"); throw invalid_argument("The path is incorrect!"); }
    if (!exists(path)) { ERROR("class AProviders -> method save_: File does not exist at path!"); throw runtime_error("File does not exist at path!"); }
    if (!file.is_open()) { ERROR("class AProviders -> method save_: Unable to open file at path!"); throw runtime_error("Unable to open file at path!"); }

    file.write(data.data(), data.size());

    INFO("class AProviders -> method save_: The operation was completed successfully!;");
    return true;
}
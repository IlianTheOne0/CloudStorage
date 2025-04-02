#include "configParser.h"

ConfigParser::ConfigParser(const string& path)
    : _path(path)
{}
ConfigParser::~ConfigParser() {}

bool ConfigParser::load()
{
    ifstream file(_path);
    if (!file.is_open()) { return false; }

    string line;
    while (getline(file, line))
    {
        if (line.empty() || line[0] == '#') { continue; }

        istringstream is_line(line);
        string key, value;
        if (getline(is_line, key, '=') && getline(is_line, value)) { _data[key] = value; }
    }

    return true;
}

string ConfigParser::get(const string& key) const
{
    map<string, string>::const_iterator iterator = _data.find(key);
    return (iterator != _data.end()) ? iterator->second : DEFAULT_VALUE;
}

bool ConfigParser::set(const string& key, const string& value) { _data[key] = value; return true; }

bool ConfigParser::save()
{
    ofstream file(_path);
    if (!file.is_open()) { return false; }

    for (const auto& pair : _data) { file << pair.first << "=" << pair.second << std::endl; }

    file.close();
    return true;
}
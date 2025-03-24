#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "../../../Infrastructure/Config/servicesConfig.h"

class ConfigParser final
{
private:
    string _path;
    map<string, string> _data;
public:
    ConfigParser() = delete;
    ConfigParser(const string& path);
    ~ConfigParser();

    bool load();
    string get(const string& key) const;
};

#endif
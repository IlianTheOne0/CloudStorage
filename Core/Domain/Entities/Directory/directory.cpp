#include "directory.h"

Directory::Directory(const string& name, const bool& isHidden)
    : Unit(name, isHidden, FileTypes::DirectoryType)
{
    ConfigParser config(CONFIG_PATH);
    if (!config.load()) { ERROR("Dirrectory <- constructor: Cannot load the config!"); throw("Cannot load the config!;"); }

    _directoryMaxSize = stoi(config.get("directoryMaxSize"));
}

vector<shared_ptr<Unit>>& Directory::getContents() { return _contents; }
const vector<shared_ptr<Unit>>& Directory::getContents() const { return _contents; }
size_t Directory::getDirectoryMaxSize() const { return _directoryMaxSize; }
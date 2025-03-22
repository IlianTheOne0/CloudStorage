#include "directory.h"

Directory::Directory(const string& name, const bool& isHidden)
    : Unit(name, isHidden, FileTypes::DirectoryType)
{ }

vector<shared_ptr<Unit>>& Directory::getContents() { return _contents; }
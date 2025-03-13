#include "directory.h"

Directory::Directory(const string& name, const bool& isHidden)
    : UnitUseCase(name, isHidden)
{ }

vector<UnitUseCase*> Directory::getData() { return _data; }
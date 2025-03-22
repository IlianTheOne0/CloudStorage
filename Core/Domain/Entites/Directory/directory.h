#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../Unit/unit.h"

class Directory
    : public Unit
{
private:
    vector<shared_ptr<Unit>> _contents;
public:
    Directory() = delete;
    Directory(const string& name, const bool& isHidden);
    ~Directory() override = default;

    vector<shared_ptr<Unit>>& getContents();
};

#endif
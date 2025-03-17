#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../UseCases/UnitUseCase/unitUseCase.h"

class Directory
    : public UnitUseCase
{
public:
    vector<UnitUseCase*> _vObjects;

    Directory() = delete;
    Directory(const string& name, const bool& isHidden);
    ~Directory() override = default;
};

#endif
#ifndef FILE_ABSTRACTION_H
#define FILE_ABSTRACTION_H

#include "../Interface/IFile.h"

#include "../../Unit/unitTypesEnum.h"
#include "../../Unit/unit.h"

class AFile abstract
	: public IFile, public Unit
{
private:
    string _data;
public:
    AFile(const string& name, const bool& isHidden, const FileTypes& fileType);
    ~AFile() override = default;

    void editContent(const string& newContent) override;
    string getContent() const override;
};

#endif
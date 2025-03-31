#ifndef FILES_USECASE_TEXTFILE_H
#define FILES_USECASE_TEXTFILE_H

#include "../../Entities/File/Abstraction/AFile.h"
#include "../../Entities/Unit/unitTypesEnum.h"

class TextFile
    : public AFile
{
public:
    TextFile() = default;
    TextFile(const string& name, const string& content, const bool& isHidden = false);
    ~TextFile() override = default;
};


#endif
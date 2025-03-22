#ifndef FILES_USECASE_TEXTFILE_H
#define FILES_USECASE_TEXTFILE_H

#include "../../Entites/File/Abstraction/AFile.h"
#include "../../Entites/Unit/unitTypesEnum.h"

class TextFile
    : public AFile
{
public:
    TextFile() = delete;
    TextFile(const string& name, const string& content, const bool& isHidden = false);
    ~TextFile() override = default;
};

#endif
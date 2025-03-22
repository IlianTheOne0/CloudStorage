#include "textFileUseCase.h"

TextFile::TextFile(const string& name, const string& content, const bool& isHidden)
    : AFile(name, isHidden, FileTypes::TextFileType)
{ editContent(content); }
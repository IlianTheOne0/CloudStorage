#include "AFile.h"

AFile::AFile(const string& name, const bool& isHidden, const FileTypes& fileType)
    : Unit(name, isHidden, fileType)
{ }

void AFile::editContent(const string& newContent) { _data = newContent; }
string AFile::getContent() const { return _data; }
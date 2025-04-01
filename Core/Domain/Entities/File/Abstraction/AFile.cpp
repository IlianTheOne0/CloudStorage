#include "AFile.h"

AFile::AFile(const string& name, const bool& isHidden, const FileTypes& fileType)
    : Unit(name, isHidden, fileType)
{ }

time_t getCurrentTimeFile() { auto now = system_clock::now(); return system_clock::to_time_t(now); }

void AFile::editContent(const string& newContent) { _data = newContent; setLastEditedDate(getCurrentTimeFile());}
string AFile::getContent() const { return _data; }
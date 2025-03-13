#include "textFile.h"

TextFiles::TextFiles(const string& name, const bool& isHidden)
	: AFilesUseCase(name, isHidden)
{ }

FileTypes TextFiles::getFileType() const { return _fileType; }
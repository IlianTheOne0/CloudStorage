#ifndef FILES_TEXT_H
#define FILES_TEXT_H

#include "../../../../../../Infrastructure/Config/domainConfig.h"

#include "../../Abstraction/AFilesUseCase.h"
#include "../../fileTypesEnum.h"

class TextFiles
	: public AFilesUseCase
{
private:
	FileTypes _fileType = FileTypes::TextFile;
public:
	TextFiles() = delete;
	TextFiles(const string& name, const bool& isHidden = false);
	~TextFiles() = default;
	
	FileTypes getFileType() const;
};

#endif
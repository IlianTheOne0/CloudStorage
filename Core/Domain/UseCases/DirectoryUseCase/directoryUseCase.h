#ifndef DIRECTORY_USECASE_H
#define DIRECTORY_USECASE_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../Entites/Directory/directory.h"

class DirectoryUseCase
{
private:
	Directory* _directory = nullptr;
	static size_t _maxSize;
public:
	DirectoryUseCase() = delete;
	DirectoryUseCase(const string& name, const bool& isHidden = false);
	virtual ~DirectoryUseCase();

	virtual void add(UnitUseCase* item);
	virtual void remove(UnitUseCase* item);

	virtual void add(const string& name);
	virtual void remove(const string& name);

	virtual map<string, string> getInfo() const;
};

#endif
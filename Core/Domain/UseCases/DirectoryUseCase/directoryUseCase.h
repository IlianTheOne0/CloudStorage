#ifndef DIRECTORY_USECASE_H
#define DIRECTORY_USECASE_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../Entites/entites.h"

class DirectoryUseCase
{
private:
	Directory* _data = nullptr;
public:
	DirectoryUseCase() = delete;
	DirectoryUseCase(const string& name, const bool& isHidden = false);
	virtual ~DirectoryUseCase();

	virtual void add(UnitUseCase* unit);
	virtual void remove(UnitUseCase* unit);

	virtual list<map<string, string>> getInfo();
};

#endif
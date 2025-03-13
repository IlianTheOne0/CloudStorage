#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../UseCases/useCases.h"

class Directory
	: public UnitUseCase
{
private:
	vector<UnitUseCase*> _data;
public:
	Directory() = delete;
	Directory(const string& name, const bool& isHidden);
	~Directory() override = default;

	vector<UnitUseCase*> getData();
	void operator->() { updateLastEdited; }
};

#endif
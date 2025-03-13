#include "directoryUseCase.h"

DirectoryUseCase::DirectoryUseCase(const string& name, const bool& isHidden)
	: _data(new Directory(name, isHidden))
{ }
DirectoryUseCase::~DirectoryUseCase() { if (_data) { delete _data; } }

void DirectoryUseCase::add(UnitUseCase* unit) { _data->getData().push_back(unit); }
void DirectoryUseCase::remove(UnitUseCase* unit)
{
	vector<UnitUseCase*>::iterator iterator = find(_data->getData().begin(), _data->getData().end(), unit);
	if (iterator != _data->getData().end()) { _data->getData().erase(iterator); }
}

list<map<string, string>> DirectoryUseCase::getInfo()
{
	list<map<string, string>> result;

	for (const UnitUseCase* unit : _data->getData()) { result.push_back(unit->getInfo()); }

	return result;
}
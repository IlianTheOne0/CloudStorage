#include "unitUseCase.h"

void UnitUseCase::updateLastEdited() { _data->setLastEditedDate(time(nullptr)); }

UnitUseCase::UnitUseCase(const string& name, const bool& isHidden)
	: _data(new Unit(name, isHidden))
{ }
UnitUseCase::~UnitUseCase() { if (_data) { delete _data; } }

void UnitUseCase::rename(const string& value) { _data->setName(value); updateLastEdited(); }
void UnitUseCase::setHidden(const bool& value) { _data->setIsHidden(value); updateLastEdited(); }

map<string, string> UnitUseCase::getInfo() const
{
	map<string, string> result;

	result.emplace("name", _data->getName());
	result.emplace("isHidden", (_data->getIsHidden() ? "Yes" : "No"));
	result.emplace("created", _data->getCreatedDate());
	result.emplace("lastEdited", _data->getLastEditedDate());

	return result;
}
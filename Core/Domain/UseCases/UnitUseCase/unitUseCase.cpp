#include "unitUseCase.h"

void UnitUseCase::updateLastEdited() { _unit->setLastEditedDate(time(nullptr)); }

UnitUseCase::UnitUseCase(const string& name, const bool& isHidden)
	: _unit(new Unit(name, isHidden))
{ }
UnitUseCase::~UnitUseCase() { if (_unit) { delete _unit; } }

void UnitUseCase::rename(const string& value) { _unit->setName(value); }
void UnitUseCase::setHidden(const bool& value) { _unit->setIsHidden(value); }

map<string, string> UnitUseCase::getInfo() const
{
	map<string, string> result;

	auto timeToString = [](time_t time)
		{
			tm tm;
			localtime_s(&tm, &time);
			
			ostringstream stream;
			stream << put_time(&tm, "%Y-%m-%d %H:%M:%S");
			return stream.str();
		};

	result.emplace("name", _unit->getName());
	result.emplace("isHidden", (_unit->getIsHidden() ? "Yes" : "No"));
	result.emplace("created", timeToString(_unit->getCreatedDate()));
	result.emplace("lastEdited", timeToString(_unit->getLastEditedDate()));

	return result;
}
Unit* UnitUseCase::getUnit() const { return _unit; }
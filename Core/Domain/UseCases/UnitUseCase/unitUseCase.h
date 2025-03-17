#ifndef UNIT_USECASE_H
#define UNIT_USECASE_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../Entites/Unit/unit.h"

class UnitUseCase
{
private:
	Unit* _unit = nullptr;
	virtual void updateLastEdited();
public:
	UnitUseCase() = delete;
	UnitUseCase(const string& name, const bool& isHidden = false);
	virtual ~UnitUseCase();

	virtual void rename(const string& value);
	virtual void setHidden(const bool& value);

	virtual map<string, string> getInfo() const;
	Unit* getUnit() const;

	Unit* operator->() { updateLastEdited(); return _unit; }
};

#endif
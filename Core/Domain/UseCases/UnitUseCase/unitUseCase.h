#ifndef UNIT_USECASE_H
#define UNIT_USECASE_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../Entites/entites.h"

class UnitUseCase
{
private:
	Unit* _data = nullptr;
protected:
	virtual void updateLastEdited();
public:
	UnitUseCase() = delete;
	UnitUseCase(const string& name, const bool& isHidden = false);
	virtual ~UnitUseCase();

	virtual void rename(const string& value);
	virtual void setHidden(const bool& value);

	virtual map<string, string> getInfo() const;
};

#endif
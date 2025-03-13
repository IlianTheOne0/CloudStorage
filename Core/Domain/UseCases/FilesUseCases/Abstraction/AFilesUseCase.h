#ifndef FILES_USECASE_ABSTRACTION_H
#define FILES_USECASE_ABSTRACTION_H

#include "../Interface/IFilesUseCase.h"
#include "../../../UseCases/UnitUseCase/unitUseCase.h"

class AFilesUseCase
	: public IFilesUseCase, public UnitUseCase
{
private:
	string _content;
public:
	AFilesUseCase() = delete;
	AFilesUseCase(const string& name, bool isHidden);
	~AFilesUseCase() override = default;

	string getContent() const;
	void edit(const string& value) override;
};

#endif
#include "AFilesUseCase.h"

AFilesUseCase::AFilesUseCase(const string& name, bool isHidden)
	: UnitUseCase(name, isHidden)
{ }

string AFilesUseCase::getContent() const { return _content; }
void AFilesUseCase::edit(const string& value) { _content = value; updateLastEdited(); }
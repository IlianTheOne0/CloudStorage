#include "unit.h"

Unit::Unit(const string& name, const bool& isHidden, const FileTypes& fileType)
    : _name(name), _isHidden(isHidden), _fileType(fileType)
{
    _createdDate = time(nullptr);
    _lastEditedDate = _createdDate;
}

string Unit::getName() const { return _name; }
bool Unit::getIsHidden() const { return _isHidden; }
time_t Unit::getCreatedDate() const { return _createdDate; }
time_t Unit::getLastEditedDate() const { return _lastEditedDate; }
FileTypes Unit::getFileType() const { return _fileType; }

void Unit::setName(const string& value) { _name = value; }
void Unit::setIsHidden(const bool& value) { _isHidden = value; }
void Unit::setCreatedDate(const time_t& value) { _createdDate = value; }
void Unit::setLastEditedDate(const time_t& value) { _lastEditedDate = value; }
void Unit::setFileType(const FileTypes& value) { _fileType = value; }
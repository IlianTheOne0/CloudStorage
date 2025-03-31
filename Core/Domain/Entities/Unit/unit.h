#ifndef UNIT_H
#define UNIT_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "unitTypesEnum.h"

class Unit {
private:
    string _name;
    bool _isHidden;
    time_t _createdDate;
    time_t _lastEditedDate;
    FileTypes _fileType;
public:
    Unit() = delete;
    Unit(const string& name, const bool& isHidden, const FileTypes& fileType);
    virtual ~Unit() = default;

    string getName() const;
    bool getIsHidden() const;
    time_t getCreatedDate() const;
    time_t getLastEditedDate() const;
    FileTypes getFileType() const;

    void setName(const string& value);
    void setIsHidden(const bool& value);
    void setCreatedDate(const time_t& value);
    void setLastEditedDate(const time_t& value);
    void setFileType(const FileTypes& value);
};

#endif
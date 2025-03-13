#ifndef UNIT_H
#define UNIT_H

#include "../../../../Infrastructure/Config/domainConfig.h"

class Unit {
private:
    string _name;
    bool _isHidden;
    time_t _createdDate;
    time_t _lastEditedDate;
public:
    Unit() = delete;
    Unit(const string& name, bool isHidden);
    virtual ~Unit() = default;

    string getName() const;
    bool getIsHidden() const;
    time_t getCreatedDate() const;
    time_t getLastEditedDate() const;

    void setName(const string& value);
    void setIsHidden(const bool& value);
    void setCreatedDate(const time_t& value);
    void setLastEditedDate(const time_t& value);
};

#endif
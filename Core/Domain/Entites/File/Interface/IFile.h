#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H

#include "../../../../../Infrastructure/Config/domainConfig.h"

class IFile
{
public:
    virtual ~IFile() = default;

    virtual void editContent(const string& newContent) = 0;
    virtual string getContent() const = 0;
};

#endif
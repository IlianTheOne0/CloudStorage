#ifndef DIRECTORY_USECASE_H
#define DIRECTORY_USECASE_H

#include "../../../../Infrastructure/Config/domainConfig.h"

#include "../../Entites/Directory/directory.h"

class DirectoryUseCase
{
public:
    static void addByParams(shared_ptr<Directory>& directory, const string& name, const FileTypes& fileType, const bool& isHidden = false);
    static void addByUnit(shared_ptr<Directory>& directory, const shared_ptr<Unit>& unit);

    static void remove(shared_ptr<Directory>& directory, const string& name);

    static bool switchToDirectory(shared_ptr<Directory>& directory, const string& name);
};

#endif
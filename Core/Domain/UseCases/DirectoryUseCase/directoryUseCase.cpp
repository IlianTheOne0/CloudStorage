#include "directoryUseCase.h"

void DirectoryUseCase::add(shared_ptr<Directory>& directory, const string& name, const FileTypes& fileType, const bool& isHidden)
{
    if (!directory) { throw invalid_argument("Directory pointer is null!"); }

    switch (fileType)
    {
    case FileTypes::DirectoryType: { directory->getContents().push_back(make_shared<Directory>(name, isHidden)); } break;
    default: { directory->getContents().push_back(make_shared<Unit>(name, isHidden, fileType)); }
    }
}
void DirectoryUseCase::add(shared_ptr<Directory>& directory, const shared_ptr<Unit>& unit)
{
    if (!directory) { throw invalid_argument("Directory pointer is null!"); }
    if (!unit) { throw invalid_argument("Unit pointer is null!"); }

    directory->getContents().push_back(unit);
}

void DirectoryUseCase::remove(shared_ptr<Directory>& directory, const string& name)
{
    if (!directory) { throw invalid_argument("Directory pointer is null!"); }

    vector<shared_ptr<Unit>>::iterator it = remove_if(directory->getContents().begin(), directory->getContents().end(),
        [&name](const shared_ptr<Unit>& unit) { return unit->getName() == name; });

    if (it == directory->getContents().end()) { throw runtime_error("Unit with the specified name not found!"); }
    directory->getContents().erase(it, directory->getContents().end());
}

bool DirectoryUseCase::switchToDirectory(shared_ptr<Directory>& directory, const string& name)
{
    if (!directory) { throw invalid_argument("Directory pointer is null!"); }

    for (const shared_ptr<Unit>& unit : directory->getContents())
    {
        if (unit->getFileType() == FileTypes::DirectoryType && unit->getName() == name)
        {
            shared_ptr<Directory> newDirectory = dynamic_pointer_cast<Directory>(unit);
            if (newDirectory) { directory = newDirectory; return true; }
            else { throw runtime_error("Failed to cast Unit to Directory!"); }
        }
    }
    return false;
}
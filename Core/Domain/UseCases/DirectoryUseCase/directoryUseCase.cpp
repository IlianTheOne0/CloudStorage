#include "directoryUseCase.h"

void DirectoryUseCase::addByParams(shared_ptr<Directory>& directory, const string& name, const FileTypes& fileType, const bool& isHidden)
{
    INFO("class DirectoryUseCase -> static method add: Creating by parameters;");

    if (!directory) { ERROR("class DirectoryUseCase -> static method add: Directory pointer is null!"); throw invalid_argument("Directory pointer is null!"); }
    if (directory->getContents().size() >= directory->getDirectoryMaxSize()) { ERROR("class DirectoryUseCase -> static method add: Directory has reached its maximum size!"); throw runtime_error("Directory has reached its maximum size!"); }

    switch (fileType)
    {
        case FileTypes::DirectoryType: { INFO("class DirectoryUseCase -> static method add: Adding a directory;"); directory->getContents().push_back(make_shared<Directory>(name, isHidden)); } break;
        default: { INFO("class DirectoryUseCase -> static method add: Adding a unit;"); directory->getContents().push_back(make_shared<Unit>(name, isHidden, fileType)); }
    }

    INFO("class DirectoryUseCase -> static method add: The operation was completed successfully!;");
}
void DirectoryUseCase::addByUnit(shared_ptr<Directory>& directory, const shared_ptr<Unit>& unit)
{
    INFO("class DirectoryUseCase -> static method add: Creating by unit;");

    if (!directory) { ERROR("class DirectoryUseCase -> static method add: Directory pointer is null!"); throw invalid_argument("Directory pointer is null!"); }
    if (directory->getContents().size() >= directory->getDirectoryMaxSize()) { ERROR("class DirectoryUseCase -> static method add: Directory has reached its maximum size!"); throw runtime_error("Directory has reached its maximum size!"); }
    if (!unit) { ERROR("class DirectoryUseCase -> static method add: Unit pointer is null!"); throw invalid_argument("Unit pointer is null!"); }

    directory->getContents().push_back(unit);

    INFO("class DirectoryUseCase -> static method add: The operation was completed successfully!;");
}

void DirectoryUseCase::remove(shared_ptr<Directory>& directory, const string& name)
{
    if (!directory) { ERROR("class DirectoryUseCase -> static method remove: Directory pointer is null!"); throw invalid_argument("Directory pointer is null!"); }

    vector<shared_ptr<Unit>>::iterator it = remove_if(directory->getContents().begin(), directory->getContents().end(),
        [&name](const shared_ptr<Unit>& unit) { return unit->getName() == name; });

    if (it == directory->getContents().end()) { ERROR("class DirectoryUseCase -> remove: Unit with the specified name not found!;"); throw runtime_error("Unit with the specified name not found!"); }
    directory->getContents().erase(it, directory->getContents().end());

    INFO("class DirectoryUseCase -> static method remove: The operation was completed successfully!;");
}

bool DirectoryUseCase::switchToDirectory(shared_ptr<Directory>& directory, const string& name)
{
    if (!directory) { ERROR("class DirectoryUseCase -> static method switchToDirectory: Directory pointer is null!"); throw invalid_argument("Directory pointer is null!"); }

    for (const shared_ptr<Unit>& unit : directory->getContents())
    {
        if (unit->getFileType() == FileTypes::DirectoryType && unit->getName() == name)
        {
            shared_ptr<Directory> newDirectory = dynamic_pointer_cast<Directory>(unit);
            if (newDirectory) { directory = newDirectory; return true; }
            else { ERROR("class DirectoryUseCase -> static method switchToDirectory: Failed to cast Unit to Directory!"); throw runtime_error("Failed to cast Unit to Directory!"); }
        }
    }
    return false;
}
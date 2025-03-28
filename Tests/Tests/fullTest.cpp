#include "../testHandler.h"
#include "../../Infrastructure/Config/servicesConfig.h"
#include "../../Core/core.h"

void printResult(const string& operation, bool success) { cout << "[" << (success ? "OK" : "FAILED") << "] " << operation << endl; }

void printSectionHeader(const string& message)
{
    cout << endl;
    for (int i = 0; i < 50; i++) { cout << '='; } cout << endl;
    for (int i = 0; i < ((50 / 2) - (message.size() / 2)) - 2; i++) { cout << ' '; }
    cout << " " << message << endl;
    for (int i = 0; i < 50; i++) { cout << '='; } cout << endl;
}

void validateHiddenStatus(shared_ptr<Directory> dir, bool expected)
{
    bool actual = dir->getIsHidden();
    
    cout << "Hidden status: " << (actual ? "Yes" : "No") << " | Expected: " << (expected ? "Yes" : "No") << endl;
    if (actual != expected) { throw runtime_error("Hidden status mismatch!"); }
}

void simulateSession1()
{
    printSectionHeader("SESSION 1 - Initial Setup");

    Wrapper<Directory> root("root", false);
    auto rootDir = root.get();
    cout << "Created root directory" << endl;

    StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByParams, "addByParams", rootDir, "Documents", FileTypes::DirectoryType, false);
    bool addDocResult = rootDir->getContents().size() == 1;
    printResult("Add Documents directory", addDocResult);

    shared_ptr<Directory> currentDir = rootDir;
    bool switchResult = StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::switchToDirectory, "switchToDirectory", currentDir, "Documents");
    printResult("Navigate to Documents", switchResult);

    Wrapper<TextFile> notes("notes.txt", "Initial content", false);
    StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByUnit, "addByUnit", currentDir, notes.get() );
    bool addNotesResult = currentDir->getContents().size() == 1;
    printResult("Create notes.txt", addNotesResult);

    string serialized = Serializer::serializeDirectory(root.get().get());
    cout << "Serialized data length: " << serialized.length() << " bytes" << endl;
    bool saveResult = DataSyncUseCase::setData(serialized);
    printResult("Save session state", saveResult);

    cout
        << endl << "Final Session 1 Structure:" << endl
        << "root/" << endl
        << "|-- Documents (DIR)" << endl
        << "    |-- notes.txt (FILE)" << endl;
}

void simulateSession2()
{
    printSectionHeader("SESSION 2 - Content Modification");

    string serialized = DataSyncUseCase::getData();
    shared_ptr<Unit> loadedUnit = Serializer::deserialize(serialized);
    bool loadSuccess = loadedUnit != nullptr && loadedUnit->getFileType() == FileTypes::DirectoryType;
    printResult("Load session state", loadSuccess);

    if (!loadSuccess) { return; }

    Wrapper<Directory> wrappedRoot(*dynamic_pointer_cast<Directory>(loadedUnit));
    cout << "Loaded root directory" << endl;

    shared_ptr<Directory> currentDir = wrappedRoot.get();
    bool switchResult = StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::switchToDirectory, "switchToDirectory", currentDir, "Documents");
    printResult("Navigate to Documents", switchResult);

    bool foundNotes = false;
    auto& contents = currentDir->getContents();
    for (auto& item : contents)
    {
        if (item->getFileType() == FileTypes::TextFileType)
        {
            if (auto file = dynamic_pointer_cast<AFile>(item))
            {
                cout << endl << "Updating file: " << file->getName() << endl << "Original content: " << file->getContent() << endl;
                file->editContent("Updated content with user notes");
                cout << "New content: " << file->getContent() << endl;
                foundNotes = true;
            }
        }
    }
    printResult("Update notes.txt content", foundNotes);

    StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByParams, "addByParams", currentDir, "Projects", FileTypes::DirectoryType, true);
    bool addProjResult = currentDir->getContents().size() == 2;
    printResult("Create hidden Projects directory", addProjResult);

    for (auto& item : currentDir->getContents())
    {
        if (item->getName() == "Projects")
        {
            auto projectsDir = dynamic_pointer_cast<Directory>(item);

            if (projectsDir)
            {
                try { cout << "Validating Projects directory creation:" << endl; validateHiddenStatus(projectsDir, true); }
                catch (const exception& e) { printResult("Hidden status validation", false); return; }
            }
        }
    }

    string newSerialized = Serializer::serializeDirectory(wrappedRoot.get().get());
    bool saveResult = DataSyncUseCase::setData(newSerialized);
    printResult("Save modified state", saveResult);
}

void simulateSession3()
{
    printSectionHeader("SESSION 3 - Final Structure");

    string serialized = DataSyncUseCase::getData();
    cout << "Serialized: " << serialized << endl;
    shared_ptr<Unit> loadedUnit = Serializer::deserialize(serialized);
    bool loadSuccess = loadedUnit != nullptr && loadedUnit->getFileType() == FileTypes::DirectoryType;
    printResult("Load session state", loadSuccess);

    if (!loadSuccess) { return; }

    Wrapper<Directory> wrappedRoot(*dynamic_pointer_cast<Directory>(loadedUnit));
    cout << "Loaded root directory" << endl;

    vector<tuple<string, bool, size_t>> navigationPath = { {"Documents", false, 2}, {"Projects", true, 0} };

    shared_ptr<Directory> currentDir = wrappedRoot.get();
    for (const auto& [targetDir, expectedHidden, expectedCount] : navigationPath)
    {
        bool switchResult = StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::switchToDirectory, "switchToDirectory", currentDir, targetDir );

        if (!switchResult) { printResult("Navigate to " + targetDir, false); return; }

        try
        {
            cout << endl << "Validating " << targetDir << " directory:" << endl;
            validateHiddenStatus(currentDir, expectedHidden);
            cout << "Item count: " << currentDir->getContents().size() << " | Expected: " << expectedCount << endl;

            if (currentDir->getContents().size() != expectedCount) { throw runtime_error("Item count mismatch!"); }

            printResult("Navigate to " + targetDir, true);
        }
        catch (const exception& e) { printResult(string("Validation failed: ") + e.what(), false); return; }
    }

    Wrapper<TextFile> projectFile("project.txt", "Codebase...", false);
    StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByUnit, "addByUnit", currentDir, projectFile.get() );
    bool addFileResult = currentDir->getContents().size() == 1;
    printResult("Add project.txt", addFileResult);

    try
    {
        cout << endl << "Final validation:" << endl;
        validateHiddenStatus(currentDir, true);
        cout << "Final item count: " << currentDir->getContents().size() << endl;

        if (auto file = dynamic_pointer_cast<AFile>(currentDir->getContents()[0])) { cout << "File content validation: " << file->getContent() << endl; }

        printResult("Final structure validation", true);
    }
    catch (const exception& e) { printResult(string("Final validation failed: ") + e.what(), false); }

    bool syncResult = StaticWrapper<DataSyncUseCase>::call()(&DataSyncUseCase::synkFromLocal, "synkFromLocal" );
    printResult("Sync to remote", syncResult);
}

void TestHandler::fullTest()
{
    try
    {
        simulateSession1();
        simulateSession2();
        simulateSession3();
        printSectionHeader("All operations completed successfully");
    }
    catch (const exception& e) { printSectionHeader("Test failed: " + string(e.what())); }
}
#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/core.h"

void TestHandler::directoryTest()
{
    shared_ptr<Directory> rootDirectory = make_shared<Directory>("root", false);
    Wrapper<Directory> root(*rootDirectory);

    try
    {
        StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByParams, "addByParams", rootDirectory, "directory01", FileTypes::DirectoryType, false);
        root = Wrapper<Directory>(*rootDirectory);
        cout << "Contents size after adding directory01: " << root.call()(static_cast<vector<shared_ptr<Unit>>&(Directory::*)()>(&Directory::getContents), "getContents").size() << endl;
    }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }
    
    try
    {
        StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByParams, "addByParams", rootDirectory, "directory02", FileTypes::DirectoryType, false);
        root = Wrapper<Directory>(*rootDirectory);
        cout << "Contents size after adding directory02: " << root.call()(static_cast<vector<shared_ptr<Unit>>&(Directory::*)()>(&Directory::getContents), "getContents").size() << endl;
    }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }

    shared_ptr<TextFile> file01 = make_shared<TextFile>("file01.txt", "This is file 01 content.");
    shared_ptr<TextFile> file02 = make_shared<TextFile>("file02.txt", "This is file 02 content.");

    try
    {
        StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByUnit, "addByUnit", rootDirectory, file01);
        root = Wrapper<Directory>(*rootDirectory);
        cout << "Contents size after adding file01: " << root.call()(static_cast<vector<shared_ptr<Unit>>&(Directory::*)()>(&Directory::getContents), "getContents").size() << endl;
    }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }

    try
    {
        StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByUnit, "addByUnit", rootDirectory, file02);
        root = Wrapper<Directory>(*rootDirectory);
        cout << "Contents size after adding file02: " << root.call()(static_cast<vector<shared_ptr<Unit>>&(Directory::*)()>(&Directory::getContents), "getContents").size() << endl;
    }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }

    cout << "Contents of root directory before removal:" << endl;
    cout << root.call()(static_cast<vector<shared_ptr<Unit>>&(Directory::*)()>(&Directory::getContents), "getContents").size() << endl;
    for (const shared_ptr<Unit>& unit : root.call()(static_cast<vector<shared_ptr<Unit>>& (Directory::*)()>(&Directory::getContents), "getContents")) { cout << "- " << unit->getName() << endl; }

    cout << "\nRemoving file01.txt..." << endl;
    try { StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::remove, "remove", rootDirectory, "file01.txt"); }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }
    root = Wrapper<Directory>(*rootDirectory);

    cout << "\nContents of root directory after removing file01.txt:" << endl;
    for (const shared_ptr<Unit>& unit : root.call()(static_cast<vector<shared_ptr<Unit>>& (Directory::*)()>(&Directory::getContents), "getContents")) { cout << "- " << unit->getName() << endl; }

    cout << "\nSwitching to directory02..." << endl;
    try
    {
        bool switched = StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::switchToDirectory, "switchToDirectory", rootDirectory, "directory02");

        if (switched) { cout << "Switched to directory02 successfully!" << endl; }
        else { cout << "Failed to switch to directory02!" << endl; }
    }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }
    root = Wrapper<Directory>(*rootDirectory);

    shared_ptr<TextFile> file03 = make_shared<TextFile>("file03.txt", "This is file 03 content.");
    cout << "\nCreating file03.txt" << endl;
    try
    {
        StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::addByUnit, "addByUnit", rootDirectory, file03);
        root = Wrapper<Directory>(*rootDirectory);
        cout << "Contents size after adding file03: " << root.call()(static_cast<vector<shared_ptr<Unit>>&(Directory::*)()>(&Directory::getContents), "getContents").size() << endl;
    }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }

    cout << "\nContents of root directory after adding file03.txt:" << endl;
    for (const shared_ptr<Unit>& unit : root.call()(static_cast<vector<shared_ptr<Unit>>& (Directory::*)()>(&Directory::getContents), "getContents")) { cout << "- " << unit->getName() << endl; }

    cout << "\nRemoving file03.txt..." << endl;
    try { StaticWrapper<DirectoryUseCase>::call()(&DirectoryUseCase::remove, "remove", rootDirectory, "file03.txt"); }
    catch (const exception& e) { cerr << "Error: " << e.what() << endl; }
    root = Wrapper<Directory>(*rootDirectory);

    cout << "\nContents of root directory after removing file03.txt:" << endl;
    for (const shared_ptr<Unit>& unit : root.call()(static_cast<vector<shared_ptr<Unit>>& (Directory::*)()>(&Directory::getContents), "getContents")) { cout << "- " << unit->getName() << endl; }
}
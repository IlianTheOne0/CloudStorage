#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/core.h"

void TestHandler::directoryTest() {
    shared_ptr<Directory> root = make_shared<Directory>("root", false);

    try { DirectoryUseCase::add(root, "directory01", FileTypes::DirectoryType); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    try { DirectoryUseCase::add(root, "directory02", FileTypes::DirectoryType); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    shared_ptr<TextFile> file01 = make_shared<TextFile>("file01.txt", "This is file 01 content.");
    shared_ptr<TextFile> file02 = make_shared<TextFile>("file02.txt", "This is file 02 content.");

    try { DirectoryUseCase::add(root, file01); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    try { DirectoryUseCase::add(root, file02); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    cout << "Contents of root directory before removal:" << endl;
    for (const shared_ptr<Unit>& unit : root->getContents()) { cout << "- " << unit->getName() << endl; }

    cout << "\nRemoving file01.txt..." << endl;
    try { DirectoryUseCase::remove(root, "file01.txt"); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    cout << "\nContents of root directory after removing file01.txt:" << endl;
    for (const shared_ptr<Unit>& unit : root->getContents()) { cout << "- " << unit->getName() << endl; }

    cout << "\nSwitching to directory02..." << endl;
    try
    {
        bool switched = DirectoryUseCase::switchToDirectory(root, "directory02");
        if (switched) { cout << "Switched to directory02 successfully!" << endl; }
        else { cout << "Failed to switch to directory02!" << endl; }
    }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }
    
    shared_ptr<TextFile> file03 = make_shared<TextFile>("file03.txt", "This is file 02 content.");
    cout << "\nCreating file03.txt" << endl;
    try { DirectoryUseCase::add(root, file03); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    cout << "\nContents of root directory after addinf file03.txt:" << endl;
    for (const shared_ptr<Unit>& unit : root->getContents()) { cout << "- " << unit->getName() << endl; }

    cout << "\nRemoving file03.txt..." << endl;
    try { DirectoryUseCase::remove(root, "file03.txt"); }
    catch (const exception& e) { cout << "Error: " << e.what() << endl; }

    cout << "\nContents of root directory after removing file03.txt:" << endl;
    for (const shared_ptr<Unit>& unit : root->getContents()) { cout << "- " << unit->getName() << endl; }
}
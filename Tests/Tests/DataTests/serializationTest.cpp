#include "../../testHandler.h"
#include "../../../Infrastructure/Config/servicesConfig.h"
#include "../../../Core/core.h"

void testSerializationDeserialization();
void printDirectory(const shared_ptr<Directory>& directory);

void testSerializationDeserialization()
{
    shared_ptr<Directory> rootDirectory = make_shared<Directory>("root", false);
    Wrapper<Directory> root(*rootDirectory);

    shared_ptr<Directory> folder1 = make_shared<Directory>("folder1", false);
    Wrapper<Directory> wrappedFolder1(*folder1);
    shared_ptr<Directory> folder2 = make_shared<Directory>("folder2", false);
    Wrapper<Directory> wrappedFolder2(*folder2);

    rootDirectory->getContents().push_back(folder1);
    rootDirectory->getContents().push_back(folder2);

    Wrapper<Directory> currentDir(*folder1);
    shared_ptr<TextFile> file1 = make_shared<TextFile>("file1.txt", "Content of file1", false);
    Wrapper<TextFile> wrappedFile1(*file1);
    folder1->getContents().push_back(file1);
    cout << "Contents of folder1 after adding file1:" << endl;
    printDirectory(folder1);
    cout << endl << endl;

    currentDir = Wrapper<Directory>(*rootDirectory);

    currentDir = Wrapper<Directory>(*folder2);
    shared_ptr<TextFile> file2 = make_shared<TextFile>("file2.txt", "Content of file2", false);
    Wrapper<TextFile> wrappedFile2(*file2);
    folder2->getContents().push_back(file2);
    cout << "Contents of folder2 after adding file2:" << endl;
    printDirectory(folder2);
    cout << endl << endl;

    currentDir = Wrapper<Directory>(*rootDirectory);

    currentDir = Wrapper<Directory>(*folder1);
    cout << "Contents of folder1:" << endl;
    printDirectory(folder1);
    cout << endl << endl;

    string serialized = Serializer::serializeDirectory(rootDirectory.get());
    cout << "Serialized: " << serialized << endl;
    cout << endl << endl;

    shared_ptr<Unit> restoredUnit = Serializer::deserialize(serialized);
    shared_ptr<Directory> restoredDir = dynamic_pointer_cast<Directory>(restoredUnit);
    Wrapper<Directory> wrappedRestoredDir(*restoredDir);

    cout << "Restored directory structure:" << endl;
    printDirectory(restoredDir);
    cout << endl << endl;
}

void printDirectory(const shared_ptr<Directory>& directory)
{
    cout << "Directory: " << directory->getName() << endl;

    for (const shared_ptr<Unit>& unit : directory->getContents())
    {
        if (shared_ptr<Directory> dir = dynamic_pointer_cast<Directory>(unit)) { printDirectory(dir); }
        else if (shared_ptr<TextFile> file = dynamic_pointer_cast<TextFile>(unit)) { cout << "File: " << file->getName() << " Content: " << file->getContent() << endl; }
    }
}

void TestHandler::serializationTest()
{
    testSerializationDeserialization();
}
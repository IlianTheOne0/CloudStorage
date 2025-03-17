#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/Domain/domain.h"

void addFolders(DirectoryUseCase& directory, int count)
{
    for (int i = 0; i < count; ++i)
    {
        ostringstream folderName;
        folderName << "folder" << setw(3) << setfill('0') << i;
        directory.add(new UnitUseCase(folderName.str()));
    }
}

void displayInfo(const DirectoryUseCase& directory)
{
    map<string, string> info = directory.getInfo();
    for (const auto& entry : info) { cout << entry.first << ": " << entry.second << endl; } cout << endl;
}

void deleteRandomFolders(DirectoryUseCase& directory, int count)
{
    map<string, string> info = directory.getInfo();
    vector<string> folderNames;

    for (const auto& entry : info) { if (entry.first.find("directory") == 0 && entry.first.find("_name") != string::npos) { folderNames.push_back(entry.second); } }

    if (count > folderNames.size()) { count = folderNames.size(); }

    random_device rd;
    mt19937 gen(rd());
    shuffle(folderNames.begin(), folderNames.end(), gen);

    for (int i = 0; i < count; ++i) { directory.remove(folderNames[i]); }
}

void testDirectoryOperations()
{
    DirectoryUseCase directory("root");

    addFolders(directory, 100);

    cout << "Directory information after adding 100 folders:" << endl;
    displayInfo(directory);

    deleteRandomFolders(directory, 50);

    cout << "Directory information after deleting 50 random folders:" << endl;
    displayInfo(directory);
}

void TestHandler::directoryTest() { testDirectoryOperations(); }
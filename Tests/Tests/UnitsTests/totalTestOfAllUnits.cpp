#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/Domain/domain.h"

void addFoldersAll(DirectoryUseCase& directory, int count)
{
    for (int i = 0; i < count; ++i)
    {
        ostringstream folderName;
        folderName << "folder" << setw(3) << setfill('0') << i;
        directory.add(new UnitUseCase(folderName.str()));
    }
}

void displayInfoAll(const DirectoryUseCase& directory)
{
    vector<map<string, string>> info = directory.getInfo();
    for (const auto& entry : info)
    {
        for (const auto& pair : entry)
        {
            cout << pair.first << ": " << pair.second << endl;
        }
        cout << endl;
    }
}

void deleteRandomFoldersAll(DirectoryUseCase& directory, int count)
{
    vector<map<string, string>> info = directory.getInfo();
    vector<string> folderNames;

    for (const auto& entry : info)
    {
        if (entry.at("type") == "directory")
        {
            folderNames.push_back(entry.at("name"));
        }
    }

    if (count > folderNames.size()) { count = folderNames.size(); }

    random_device rd;
    mt19937 gen(rd());
    shuffle(folderNames.begin(), folderNames.end(), gen);

    for (int i = 0; i < count; ++i)
    {
        directory.remove(folderNames[i]);
    }
}

void testDirectoryOperationsAll()
{
    DirectoryUseCase directory("root");

    addFoldersAll(directory, 100);

    cout << "Directory information after adding 100 folders:" << endl;
    displayInfoAll(directory);

    deleteRandomFoldersAll(directory, 50);

    cout << "Directory information after deleting 50 random folders:" << endl;
    displayInfoAll(directory);
}

void TestHandler::totalTestOfAllUnits() { testDirectoryOperationsAll(); }
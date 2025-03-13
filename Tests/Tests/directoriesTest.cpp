#include "../testHandler.h"
#include "../../Infrastructure/Config/testConfig.h"
#include "../../Core/Domain/UseCases/DirectoryUseCase/directoryUseCase.h"
#include "../../Core/Domain/UseCases/UnitUseCase/unitUseCase.h"

void testAddUnitToDirectory()
{
    DirectoryUseCase directory("TestDirectory");
    UnitUseCase* unit1 = new UnitUseCase("Unit1", false);
    directory.add(unit1);

    auto info = directory.getInfo();
    
    if (info.size() == 1 && info.front()["name"] == "Unit1") { cout << "Test case 'Add a unit to the directory' passed." << endl; }
    else { cout << "Test case 'Add a unit to the directory' failed." << endl; }

    delete unit1;
}

void testRemoveUnitFromDirectory()
{
    DirectoryUseCase directory("TestDirectory");
    UnitUseCase* unit1 = new UnitUseCase("Unit1", false);
    UnitUseCase* unit2 = new UnitUseCase("Unit2", false);
    directory.add(unit1);
    directory.add(unit2);

    directory.remove(unit1);
    auto info = directory.getInfo();
    
    if (info.size() == 1 && info.front()["name"] == "Unit2") { cout << "Test case 'Remove a unit from the directory' passed." << endl; }
    else { cout << "Test case 'Remove a unit from the directory' failed." << endl; }

    delete unit1;
    delete unit2;
}

void testGetInfoFromEmptyDirectory()
{
    DirectoryUseCase directory("TestDirectory");
    auto info = directory.getInfo();
    
    if (info.empty()) { cout << "Test case 'Get info from an empty directory' passed." << endl; }
    else { cout << "Test case 'Get info from an empty directory' failed." << endl; }
}

void testAddMultipleUnitsToDirectory()
{
    DirectoryUseCase directory("TestDirectory");
    UnitUseCase* unit1 = new UnitUseCase("Unit1", false);
    UnitUseCase* unit2 = new UnitUseCase("Unit2", false);
    UnitUseCase* unit3 = new UnitUseCase("Unit3", false);
    directory.add(unit1);
    directory.add(unit2);
    directory.add(unit3);

    auto info = directory.getInfo();
    
    if (info.size() == 3) { cout << "Test case 'Add multiple units to the directory' passed." << endl; }
    else { cout << "Test case 'Add multiple units to the directory' failed." << endl; }

    delete unit1;
    delete unit2;
    delete unit3;
}

void TestHandler::directoriesTest()
{
    testAddUnitToDirectory();
    testRemoveUnitFromDirectory();
    testGetInfoFromEmptyDirectory();
    testAddMultipleUnitsToDirectory();
}
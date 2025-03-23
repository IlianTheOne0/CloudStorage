#include "../../testHandler.h"

#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/Domain/domain.h"

void testConstructor()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);
    if (unit.call()(&Unit::getName, "getName") == "TestUnit" && unit.call()(&Unit::getIsHidden, "getIsHidden") == true) { cout << "Constructor test: Succeeded" << endl; }
    else { cout << "Constructor test: Failed" << endl; }
}

void testGetName()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);

    if (unit.call()(&Unit::getName, "getName") == "TestUnit") { cout << "getName test: Succeeded" << endl; }
    else { cout << "getName test: Failed" << endl; }
}

void testGetIsHidden()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);

    if (unit.call()(&Unit::getIsHidden, "getIsHidden") == true) { cout << "getIsHidden test: Succeeded" << endl; }
    else { cout << "getIsHidden test: Failed" << endl; }
}

void testSetName()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);

    unit.call()(&Unit::setName, "setName", "NewName");
    
    if (unit.call()(&Unit::getName, "getName") == "NewName") { cout << "setName test: Succeeded" << endl; }
    else { cout << "setName test: Failed" << endl; }
}

void testSetIsHidden()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);

    unit.call()(&Unit::setIsHidden, "setIsHidden", false);
    
    if (unit.call()(&Unit::getIsHidden, "getIsHidden") == false) { cout << "setIsHidden test: Succeeded" << endl; }
    else { cout << "setIsHidden test: Failed" << endl; }
}

void testSetCreatedDate()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);

    time_t now = time(0);
    unit.call()(&Unit::setCreatedDate, "setCreatedDate", now);
    
    if (unit.call()(&Unit::getCreatedDate, "getCreatedDate") == now) { cout << "setCreatedDate test: Succeeded" << endl; }
    else { cout << "setCreatedDate test: Failed" << endl; }
}

void testSetLastEditedDate()
{
    Wrapper<Unit> unit("TestUnit", true, FileTypes::DirectoryType);

    time_t now = time(0);
    time_t later = now + 1000;
    unit.call()(&Unit::setLastEditedDate, "setLastEditedDate", later);
    
    if (unit.call()(&Unit::getLastEditedDate, "getLastEditedDate") == later) { cout << "setLastEditedDate test: Succeeded" << endl; }
    else { cout << "setLastEditedDate test: Failed" << endl; }
}

void TestHandler::unitTest()
{
    testConstructor();
    testGetName();
    testGetIsHidden();
    testSetName();
    testSetIsHidden();
    testSetCreatedDate();
    testSetLastEditedDate();
}

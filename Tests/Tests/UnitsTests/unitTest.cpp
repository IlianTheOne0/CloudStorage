#include "../../testHandler.h"

#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/Domain/domain.h"

void testConstructor()
{
    Unit unit("TestUnit", true);

    if (unit.getName() == "TestUnit" && unit.getIsHidden() == true) { cout << "Constructor test: Succeeded" << endl; }
    else { cout << "Constructor test: Failed" << endl; }
}

void testGetName()
{
    Unit unit("TestUnit", true);

    if (unit.getName() == "TestUnit") { cout << "getName test: Succeeded" << endl; }
    else { cout << "getName test: Failed" << endl; }
}

void testGetIsHidden()
{
    Unit unit("TestUnit", true);

    if (unit.getIsHidden() == true) { cout << "getIsHidden test: Succeeded" << endl; }
    else { cout << "getIsHidden test: Failed" << endl; }
}

void testSetName()
{
    Unit unit("TestUnit", true);

    unit.setName("NewName");
    
    if (unit.getName() == "NewName") { cout << "setName test: Succeeded" << endl; }
    else { cout << "setName test: Failed" << endl; }
}

void testSetIsHidden()
{
    Unit unit("TestUnit", true);

    unit.setIsHidden(false);
    
    if (unit.getIsHidden() == false) { cout << "setIsHidden test: Succeeded" << endl; }
    else { cout << "setIsHidden test: Failed" << endl; }
}

void testSetCreatedDate()
{
    Unit unit("TestUnit", true);

    time_t now = time(0);
    unit.setCreatedDate(now);
    
    if (unit.getCreatedDate() == now) { cout << "setCreatedDate test: Succeeded" << endl; }
    else { cout << "setCreatedDate test: Failed" << endl; }
}

void testSetLastEditedDate()
{
    Unit unit("TestUnit", true);

    time_t now = time(0);
    time_t later = now + 1000;
    unit.setLastEditedDate(later);
    
    if (unit.getLastEditedDate() == later) { cout << "setLastEditedDate test: Succeeded" << endl; }
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

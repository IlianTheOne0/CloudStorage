#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/core.h"

void testLocalProvider()
{
    LocalProvider localProvider;
    string testData = "Test data for LocalProvider";

    if (localProvider.save(testData))
    {
        string loadedData = localProvider.load();

        if (loadedData == testData) { cout << "LocalProvider loaded data: " << loadedData << endl; }
        else { cout << "LocalProvider failed to load correct data" << endl; }
    }
    else { cout << "LocalProvider failed to save data" << endl; }
}

void testRemoteProvider()
{
    RemoteProvider remoteProvider;
    string testData = "Test data for RemoteProvider";

    if (remoteProvider.save(testData))
    {
        string loadedData = remoteProvider.load();

        if (loadedData == testData) { cout << "RemoteProvider loaded data: " << loadedData << endl; }
        else { cout << "RemoteProvider failed to load correct data" << endl; }
    }
    else { cout << "RemoteProvider failed to save data" << endl; }
}

void TestHandler::providersTest()
{
    testLocalProvider();
    testRemoteProvider();
}
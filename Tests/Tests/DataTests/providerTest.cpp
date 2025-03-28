#include "../../testHandler.h"
#include "../../../Infrastructure/Config/testConfig.h"
#include "../../../Core/core.h"

void testLocalProvider()
{
    Wrapper<LocalProvider> localProvider;
    string localTestData = "Test data for LocalProvider";

    localProvider.call()(&LocalProvider::save, "save", localTestData);
    localProvider = Wrapper<LocalProvider>();
    string loadedData = localProvider.call()(&LocalProvider::load, "load");

    if (loadedData == localTestData) { cout << "Created LocalProvider loaded data: " << loadedData << endl; }
    else { cout << "Created LocalProvider failed to load correct data" << endl; }
}

void testRemoteProvider()
{
    Wrapper<RemoteProvider> remoteProvider;
    string remoteTestData = "Test data for RemoteProvider";

    remoteProvider.call()(&RemoteProvider::save, "save", remoteTestData);
    remoteProvider = Wrapper<RemoteProvider>();
    string loadedData = remoteProvider.call()(&RemoteProvider::load, "load");

    if (loadedData == remoteTestData) { cout << "Created RemoteProvider loaded data: " << loadedData << endl; }
    else { cout << "Created RemoteProvider failed to load correct data" << endl; }
}

void TestHandler::providerTest()
{
    testLocalProvider();
    testRemoteProvider();
}
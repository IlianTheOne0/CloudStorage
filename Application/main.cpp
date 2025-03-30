#include "../Infrastructure/Config/mainConfig.h"
#include "../Tests/testHandler.h"
#include "../Core/core.h"

int main()
{
    ConfigParser config(CONFIG_PATH);
    if (!config.load())
    {
        ERROR("Cannot load the config");
        cerr << "Error: (main) Cannot load the config" << endl;
        return 1;
    }

    Logger::setLoggerState(config.get("isLogger") == "true");
    TestHandler::setTestCounter(stoi(config.get("testCounter")));

    WARNING("Start of the program");

    TestHandler::startTheTest();

    ConsoleView view;
    Presenter presenter(&view);

    view.setTerminalPropeties();
    SetConsoleOutputCP(CP_UTF8);
    wcout << Screen::update();
    pause;
    //presenter.present({"Hi", "Hello world!"});

    WARNING("End of the program");
    return 0;
}

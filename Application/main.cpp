#include "../Infrastructure/Config/mainConfig.h"
#include "../Tests/testHandler.h"

#include <exception>
using std::exception;

int main()
{
    ConfigParser config(CONFIG_PATH);
    if (!config.load()) {
        ERROR("Cannot load the config");
        cerr << "Error: (main) Cannot load the config" << endl;
        return 1;
    }

    Logger::setLoggerState(config.get("isLogger") == "true");
    TestHandler::setTestCounter(stoi(config.get("testCounter")));

    WARNING("Start of the program");

    try { TestHandler::startTheTest(); }
    catch (const exception& e) { cerr << "Error: (test handler) " << e.what() << endl; }

    WARNING("End of the program");
    return 0;
}

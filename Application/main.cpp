#include "../Infrastructure/Config/mainConfig.h"
#include "../Tests/testHandler.h"

int main()
{
	ConfigParser config(CONFIG_PATH);
	if (!config.load()) { cerr << "Error: Cannot load the config" << endl; return 1; }
	
	Logger::setLoggerState(config.get("isLogger") == "true");
	TestHandler::setTestCounter(stoi(config.get("testCounter")));

	WARNING("Start of the program");

	TestHandler::startTheTest();

	WARNING("End of the program");
	return 0;
}
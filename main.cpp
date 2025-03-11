#include "Libs/mainConfig.h"

int main()
{
	ConfigParser config(CONFIG_PATH);
	if (!config.load()) { cerr << "Error: Cannot load the config" << endl; return 1; }
	
	Logger::setLoggerState(config.get("isLogger") == "true");

	INFO("Start of the program");



	INFO("End of the program");
	return 0;
}
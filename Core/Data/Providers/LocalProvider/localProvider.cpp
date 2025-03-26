#include "localProvider.h"

LocalProvider::LocalProvider()
{
	ConfigParser config(CONFIG_PATH);
	if (!config.load()) { ERROR("LocalProvider <- constructor: Cannot load the config"); cerr << "Error: (local provider) Cannot load the config" << endl; return; }

	_path = PathReceiver::globalPath() + config.get("localSave");
}

string LocalProvider::load() const { return load_(_path); }
bool LocalProvider::save(const string& data) { return save_(_path, data); }
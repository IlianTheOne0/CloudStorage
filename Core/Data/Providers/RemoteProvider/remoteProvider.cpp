#include "remoteProvider.h"

RemoteProvider::RemoteProvider()
{
	ConfigParser config(CONFIG_PATH);
	if (!config.load()) { ERROR("RemoteProvider <- constructor: Cannot load the config"); cerr << "Error: (local provider) Cannot load the config" << endl; return; }

	_path = PathReceiver::globalPath() + config.get("remoteSave");
}

bool RemoteProvider::save(const string& data) { return save_(_path, data); }
string RemoteProvider::load() { return load_(_path); }
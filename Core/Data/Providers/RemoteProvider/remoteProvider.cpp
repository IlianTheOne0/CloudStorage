#include "remoteProvider.h"

RemoteProvider::RemoteProvider()
{
	ConfigParser config(CONFIG_PATH);
	if (!config.load()) { ERROR("RemoteProvider <- constructor: Cannot load the config"); cerr << "Error: (local provider) Cannot load the config" << endl; return; }

	_path = PathReceiver::globalPath() + config.get("remoteSave");
}

string RemoteProvider::load() const { return load_(_path); }
bool RemoteProvider::save(const string& data) { return save_(_path, data); }
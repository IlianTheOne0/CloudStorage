#include "../screen.h"
#include "../../consoleView.h"

using namespace Screen;

shared_mutex Updater::_consoleMutex;
atomic<bool> Updater::_exitFlag(false);
atomic<bool> Updater::_isStarted(false);
shared_ptr<Directory> Updater::_rootDirectory = nullptr;
stack<shared_ptr<Directory>> Updater::_directoryStack;
wstring Updater::_path = L"root\\";
bool Updater::_padding = true;
ConfigParser Updater::_config(CONFIG_PATH);
#include "../screen.h"
#include "../../consoleView.h"

using namespace Screen;

void Updater::localGoto(int x, int y) { if (_padding) { ConsoleView::gotoxy(x, y); } else { ConsoleView::gotoxy(x - 1, y - 1); } };

void Updater::setData(const shared_ptr<Directory>& root, bool pushToStack)
{
    if (pushToStack && _rootDirectory) { _directoryStack.push(_rootDirectory); }
    _rootDirectory = root;
}

shared_ptr<Directory> Updater::getData() { return _rootDirectory; }

shared_ptr<Directory> Updater::getParentDirectory()
{
    if (!_directoryStack.empty()) { shared_ptr<Directory> parentDirectory = _directoryStack.top(); _directoryStack.pop(); return parentDirectory; }
    return nullptr;
}

bool Updater::getExitFlag() { return _exitFlag.load(); }
void Updater::setExitFlag(const bool& value) { _exitFlag = value; }

const ConfigParser& Updater::getConfig() { return _config; }
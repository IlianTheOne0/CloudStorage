#include "../../screen.h"
#include "../../../consoleView.h"
#include "../../../../../../Domain/domain.h"

using namespace Screen;

void Updater::start(Presenter& presenter)
{
    if (_isStarted.exchange(true)) { return; }

    mclear;

    ConfigParser _config(CONFIG_PATH);
    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
    bool padding = (_config.get("consolePadding") == "true");

    thread redrawThread([padding]() { Updater::redrawFrame(padding); });
    thread inputThread([&presenter, padding]() { Updater::handleInput(presenter, padding); });

    redrawThread.join();
    inputThread.join();
}

void Updater::update()
{
    if (!_exitFlag)
    {
        ConfigParser _config(CONFIG_PATH);
        if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
        bool padding = (_config.get("consolePadding") == "true");

        mclear;
        wcout << Frame::draw();
        wcout << Tree::draw(_rootDirectory);

        localGoto(padding, 6, 2);
        wcout << Clock::getCurrentDateTime();

        localGoto(padding, 32, 2);
        Updater::updatePath(); wcout << _path;

        localGoto(padding, 22, 2);
        wcout << WAITING_WSTR;
    }
    else { mclear; }
}
#include "../../screen.h"
#include "../../../consoleView.h"
#include "../../../../../../Domain/domain.h"

using namespace Screen;

void Updater::start(Presenter& presenter)
{
    if (_isStarted.exchange(true)) { return; }

    mclear;

    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
    _padding = (_config.get("consolePadding") == "true");

    thread redrawThread([]() { Updater::redrawFrame(); });
    thread inputThread([&presenter]() { Updater::handleInput(presenter); });

    redrawThread.join();
    inputThread.join();
}

void Updater::update()
{
    if (_exitFlag) { mclear; return; }

    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
    _padding = (_config.get("consolePadding") == "true");

    mclear;
    wcout << Frame::draw();
    wcout << Tree::draw(_rootDirectory);

    localGoto(3, 2);
    wcout << Clock::getCurrentDateTime();

    localGoto(32, 2);
    Updater::updatePath(); wcout << _path;

    localGoto(22, 2);
    wcout << WAITING_WSTR;

    Updater::updateText();
}
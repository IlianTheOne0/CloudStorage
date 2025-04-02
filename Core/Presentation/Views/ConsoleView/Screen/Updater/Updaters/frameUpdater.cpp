#include "../../screen.h"
#include "../../../consoleView.h"

using namespace Screen;

void Updater::redrawFrame()
{
    while (!_exitFlag)
    {
        shared_lock<shared_mutex> lock(_consoleMutex);
        mclear;
        wcout << Frame::draw();

        localGoto(6, 2);
        wcout << Clock::getCurrentDateTime();
        wcout << Tree::draw(_rootDirectory);

        localGoto(32, 2);
        Updater::updatePath(); wcout << _path;

        localGoto(22, 2);
        wcout << WAITING_WSTR;

        Updater::updateText();

        if (_padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }
        if (_exitFlag) break;

        sleep_for(seconds(UODATE_DELEY));
    }
}
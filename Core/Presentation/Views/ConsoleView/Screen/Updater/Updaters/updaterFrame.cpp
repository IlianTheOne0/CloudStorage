#include "../../screen.h"
#include "../../../consoleView.h"

using namespace Screen;

void Updater::redrawFrame(bool padding)
{
    while (!_exitFlag)
    {
        shared_lock<shared_mutex> lock(_consoleMutex);
        mclear;
        wcout << Frame::draw();

        localGoto(padding, 6, 2);
        wcout << Clock::getCurrentDateTime();
        wcout << Tree::draw(_rootDirectory);

        localGoto(padding, 32, 2);
        Updater::updatePath(); wcout << _path;

        localGoto(padding, 22, 2);
        wcout << WAITING_WSTR;

        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }
        if (_exitFlag) break;

        sleep_for(seconds(UODATE_DELEY));
    }
}
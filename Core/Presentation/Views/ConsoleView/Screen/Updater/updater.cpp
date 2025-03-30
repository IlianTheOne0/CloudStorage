#include "../screen.h"
#include "../../consoleView.h"

namespace Screen
{
    void updateClock(bool padding)
    {
        while (true)
        {
            if (padding) { ConsoleView::gotoxy(2, 2); }
            else { ConsoleView::gotoxy(1, 1); }
            wcout << Screen::Clock::getCurrentDateTime();
            sleep_for(seconds(1));
        }
    }

    void update()
    {
        ConfigParser _config(CONFIG_PATH);
        if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
        bool padding = (_config.get("consolePadding") == "true");

        clear;

        wcout << Screen::Frame::draw();

        thread clockThread([](bool padding) { updateClock(padding); }, padding);
        clockThread.detach();
    }
}
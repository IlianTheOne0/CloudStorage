#include "../screen.h"
#include "../../consoleView.h"

using namespace Screen;

wstring Clock::getCurrentDateTime()
{
    time_point<system_clock> now = system_clock::now();
    time_t now_time = system_clock::to_time_t(now);
    tm local_time;
    localtime_s(&local_time, &now_time);

    wstringstream stream;
    stream << put_time(&local_time, L"%Y-%m-%d %H:%M");
    
    return stream.str();
}
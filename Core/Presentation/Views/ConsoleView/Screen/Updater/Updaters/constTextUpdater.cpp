#include "../../screen.h"
#include "../../../consoleView.h"
#include "../../../../../../Domain/domain.h"

using namespace Screen;

#define MESSAGE_PROPERTIES "PROPERTIES"

const wchar_t* MESSAGES[] =
{
    L"rename <old name><new name>",
    L"mkdir [-h] <name>",
    L"notepad [-h] <name>",
    L"info <[nothing]/name>",
    L"change [hidden|config] ...",
    L"cd <name/..>",
    L"del <name>",
    L"open <name>",
    L"exit",
    L"update"
};

void Updater::updateText()
{
    int x = 3, y = 4;
    localGoto(x + 8, y); wcout << MESSAGE_PROPERTIES;

    y += 11;
    for (const wstring& message : MESSAGES) { localGoto(x, y++); wcout << message; }
}
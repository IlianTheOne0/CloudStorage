#include "../../screen.h"
#include "../../../consoleView.h"
#include "../../../../../../Domain/domain.h"

using namespace Screen;

#define MESSAGE_PROPERTIES "PROPERTIES"

#define MESSAGE_LINE_0 "rename <old name><new name>"
#define MESSAGE_LINE_1 "mkdir [-h] <name>"
#define MESSAGE_LINE_2 "notepad [-h] <name>"
#define MESSAGE_LINE_3 "info <[nothing]/name>"
#define MESSAGE_LINE_4 "change [hidden|config] ..."
#define MESSAGE_LINE_5 "cd <name/..>"
#define MESSAGE_LINE_6 "del <name>"
#define MESSAGE_LINE_7 "open <name>"
#define MESSAGE_LINE_8 "exit"
#define MESSAGE_LINE_9 "update"

void Updater::updateText()
{
	int x = 3, y = 4;
	localGoto(x + 8, y); wcout << MESSAGE_PROPERTIES;

	y += 11;
	localGoto(x, y++); wcout << MESSAGE_LINE_0;
	localGoto(x, y++); wcout << MESSAGE_LINE_1;
	localGoto(x, y++); wcout << MESSAGE_LINE_2;
	localGoto(x, y++); wcout << MESSAGE_LINE_3;
	localGoto(x, y++); wcout << MESSAGE_LINE_4;
	localGoto(x, y++); wcout << MESSAGE_LINE_5;
	localGoto(x, y++); wcout << MESSAGE_LINE_6;
	localGoto(x, y++); wcout << MESSAGE_LINE_7;
	localGoto(x, y++); wcout << MESSAGE_LINE_8;
	localGoto(x, y++); wcout << MESSAGE_LINE_9;
}
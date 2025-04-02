#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include "../../ViewModels/viewModel.h"

#define mclear _clear();
#define pause _pause();

void _clear();
void _pause();

class ConsoleView
{
private:
	static int _width;
	static int _height;
	static HANDLE _window;

	static ConfigParser _config;
public:
	ConsoleView();

	void setTerminalProperties();
	static pair<int, int> getTerminalSize();
	static void gotoxy(int x, int y);
};

#endif
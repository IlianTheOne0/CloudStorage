#include "../screen.h"
#include "../../consoleView.h"

namespace Screen
{
	wstring update()
	{
		clear;

		wstringstream stream;
		stream << Screen::Frame::draw();

		return stream.str();
	}
}
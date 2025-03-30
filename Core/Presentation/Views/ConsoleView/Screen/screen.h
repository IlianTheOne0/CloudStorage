#ifndef PRESENTATION_SCREEN_H
#define PRESENTATION_SCREEN_H

#include "../../../../../Infrastructure/Config/presentationConfig.h"

namespace Screen
{
	void updateClock(wstringstream& overlayStream, bool padding);
	void update();

	class Frame
	{
	private:
		static int _width;
		static int _height;
		static bool _padding;

		static void initValues();
	public:
		static wstring draw();
	};

	class Clock
	{
	public:
		static wstring getCurrentDateTime();
	};
}

#endif
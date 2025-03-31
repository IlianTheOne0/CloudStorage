#include "../screen.h"
#include "../../consoleView.h"

using namespace Screen;

int Frame::_width;
int Frame::_height;
bool Frame::_padding;

#define LEFT_TOP L'\u2554'
#define LEFT_BOTTOM L'\u255A'
#define RIGHT_TOP L'\u2557'
#define RIGHT_BOTTOM L'\u255D'
#define HORIZONTAL L'\u2550'
#define VERTICAL L'\u2551'

#define TO_RIGHT L'\u2560'
#define TO_LEFT L'\u2563'
#define TO_BOTTOM L'\u2566'
#define TO_TOP L'\u2569'
#define CROSS L'\u256c'
#define SPACE L' '

void Frame::initValues()
{
    ConfigParser _config(CONFIG_PATH);
    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }

    _padding = (_config.get("consolePadding") == "true") ? true : false;
    _width = ConsoleView::getTerminalSize().first;
    _height = ConsoleView::getTerminalSize().second;
}

wstring Frame::draw()
{
    initValues();
    wstringstream stream;

    const int leftMin = 19;
    const int middleMin = 8;
    const int rightMin = 21;
    const int separatorWidth = 1;

    const int contentWidth = _width - (_padding * 2);
    const int verticals = 2;

    int leftWidth = leftMin;
    int middleWidth = middleMin;
    int rightWidth = contentWidth - leftWidth - middleWidth - verticals;

    if (rightWidth < rightMin)
    {
        rightWidth = rightMin;
        leftWidth = max(leftMin, contentWidth - middleWidth - rightWidth - verticals);
    }

    int bottomRightWidth = rightMin;
    int bottomLeftWidth = rightWidth - bottomRightWidth - separatorWidth;

    auto drawPaddingsX = [&]() { if (_padding) stream << SPACE; };
    auto drawPaddingsY = [&]() { if (_padding) stream << endl; };

    drawPaddingsY();
    drawPaddingsX();
    stream
        << LEFT_TOP
        << setfill(HORIZONTAL) << setw(leftWidth) << TO_BOTTOM
        << setw(middleWidth + 1) << TO_BOTTOM
        << setw(rightWidth) << RIGHT_TOP << endl;

    drawPaddingsX();
    stream
        << VERTICAL << setfill(SPACE)
        << setw(leftWidth - 1) << SPACE << VERTICAL
        << setw(middleWidth) << SPACE << VERTICAL
        << setw(rightWidth - 1) << SPACE << VERTICAL << endl;

    drawPaddingsX();
    stream
        << TO_RIGHT << setfill(HORIZONTAL)
        << setw(leftWidth) << TO_TOP
        << setw(middleWidth + 1) << CROSS
        << setw(bottomLeftWidth + bottomRightWidth + 1) << TO_LEFT << endl;

    int bodyLines = _height - 4 - (_padding * 2);
    int propSplit = 10;
    int mainSplit = bodyLines - 2;

    for (int i = 0; i < bodyLines; i++)
    {
        drawPaddingsX();

        if (i == propSplit)
        {
            stream
                << TO_RIGHT
                << setfill(HORIZONTAL) << setw(leftWidth + middleWidth + separatorWidth - 1) << HORIZONTAL
                << TO_LEFT
                << setfill(SPACE) << setw(bottomLeftWidth + bottomRightWidth + separatorWidth - 1) << SPACE
                << VERTICAL;
        }
        else if (i == mainSplit)
        {
            stream
                << VERTICAL << setfill(SPACE)
                << setw(leftWidth + middleWidth + separatorWidth - 1) << SPACE
                << TO_RIGHT
                << setfill(HORIZONTAL) << setw(bottomLeftWidth + bottomRightWidth + separatorWidth - 1) << HORIZONTAL
                << TO_LEFT;
        }
        else
        {
            stream
                << VERTICAL << setfill(SPACE)
                << setw(leftWidth + middleWidth + separatorWidth - 1) << SPACE
                << VERTICAL
                << setw(bottomLeftWidth + bottomRightWidth + separatorWidth - 1) << SPACE
                << VERTICAL;
        }
        stream << endl;
    }

    drawPaddingsX();
    stream
        << LEFT_BOTTOM << setfill(HORIZONTAL)
        << setw(leftWidth + middleWidth + separatorWidth) << TO_TOP
        << setw(bottomLeftWidth + bottomRightWidth + separatorWidth) << RIGHT_BOTTOM;

    return stream.str();
}
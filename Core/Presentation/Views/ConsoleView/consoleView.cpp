#include "consoleView.h"
#include "../../../../Infrastructure/Config/presentationConfig.h"

void _clear() { if (!Logger::getLoggerState()) { system("cls"); } }
void _pause() { /*system("pause");*/ _getch(); }

HANDLE ConsoleView::_window = GetStdHandle(STD_OUTPUT_HANDLE);
ConfigParser ConsoleView::_config(CONFIG_PATH);
int ConsoleView::_width = 0;
int ConsoleView::_height = 0;

ConsoleView::ConsoleView()
{
    ConfigParser _config(CONFIG_PATH);
    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
    
    _width = stoi(_config.get("consoleWidth"));
    _height = stoi(_config.get("consoleHeight"));
}

void ConsoleView::setTerminalPropeties()
{
    if (_window == INVALID_HANDLE_VALUE) { ERROR("class ConsoleView -> static method setTerminalProperties: Unable to get the console handle!;"); throw runtime_error("Unable to get console handle"); }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(_window, &csbi);

    SMALL_RECT tempRect = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(_window, TRUE, &tempRect);

    COORD bufferSize = { static_cast<SHORT>(_width), static_cast<SHORT>(_height) };
    SetConsoleScreenBufferSize(_window, bufferSize);

    SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(_width - 1), static_cast<SHORT>(_height - 1) };
    SetConsoleWindowInfo(_window, TRUE, &windowSize);

    HWND console = GetConsoleWindow();
    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLong(console, GWL_STYLE, style);
    SetWindowPos(console, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

    _setmode(_fileno(stdout), _O_U16TEXT);
}

void ConsoleView::display(const ViewModel& viewModel)
{
    cout << viewModel.title << endl;
    cout << viewModel.message << endl;
}

pair<int, int> ConsoleView::getTerminalSize() { return pair<int, int>{_width, _height}; }
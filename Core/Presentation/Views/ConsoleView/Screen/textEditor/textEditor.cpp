#include "../screen.h"
#include "../../consoleView.h"

using namespace Screen;

void TextEditor::showCursor(bool visible)
{
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

TextEditor::TextEditor(const wstring& filename, const wstring& content)
    : _name(filename), _content(content), _cursorX(0), _cursorY(0), _scrollOffset(0)
{ if (_content.empty()) _content = L" "; }

bool TextEditor::edit()
{
    showCursor(true);
    display();

    while (true)
    {
        if (_kbhit())
        {
            int ch = _getch();

            if (ch == 0 || ch == 224) { int ext = _getch(); processKeyPress(ext); }
            else { processKeyPress(ch); }
            display();
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { showCursor(false); return false; }
        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('S') & 0x8000)) { showCursor(false); return true; }
    }
}

void TextEditor::display()
{
    mclear;

    ConsoleView::gotoxy(0, 0);
    wcout << L"Editing: " << _name << L" (Press Ctrl+S to save, Esc to cancel)\n";

    vector<wstring> lines;
    size_t pos = 0;
    while (pos < _content.size())
    {
        size_t newline = _content.find(L'\n', pos);

        if (newline == wstring::npos) { newline = _content.size(); }

        lines.push_back(_content.substr(pos, newline - pos));
        pos = newline + 1;
    }

    if (lines.empty()) { lines.push_back(L" "); }

    if (_cursorY >= lines.size()) { _cursorY = lines.size() - 1; }
    if (_cursorX > lines[_cursorY].size()) { _cursorX = lines[_cursorY].size(); }
    
    int terminalHeight = ConsoleView::getTerminalSize().second - 2;
    int linesToShow = terminalHeight - 1;

    if (_cursorY >= _scrollOffset + linesToShow) { _scrollOffset = _cursorY - linesToShow + 1; }
    else if (_cursorY < _scrollOffset) { _scrollOffset = _cursorY; }

    
    for (int i = 0; i < linesToShow; i++)
    {
        int lineIndex = i + _scrollOffset;
        ConsoleView::gotoxy(0, i + 1);

        if (lineIndex < lines.size()) { wstring line = lines[lineIndex]; if (line.empty()) line = L" "; wcout << line; }
        else { wcout << L" "; }
    }

    
    ConsoleView::gotoxy(_cursorX, (_cursorY - _scrollOffset) + 1);
}

void TextEditor::processKeyPress(int key)
{
    vector<wstring> lines;
    size_t pos = 0;

    while (pos < _content.size())
    {
        size_t newline = _content.find(L'\n', pos);

        if (newline == wstring::npos) { newline = _content.size(); }

        lines.push_back(_content.substr(pos, newline - pos));
        pos = newline + 1;
    }

    if (lines.empty()) { lines.push_back(L""); }

    switch (key)
    {
        case 72: { if (_cursorY > 0) { _cursorY--; _cursorX = (min)(_cursorX, (int)lines[_cursorY].size()); } } break;
        case 80: { if (_cursorY < lines.size() - 1) { _cursorY++; _cursorX = (min)(_cursorX, (int)lines[_cursorY].size()); } } break;
        case 75: { if (_cursorX > 0) { _cursorX--; } } break;
        case 77: { if (_cursorX < lines[_cursorY].size()) _cursorX++; } break;
        case 8:
            if (_cursorX > 0) { lines[_cursorY].erase(_cursorX - 1, 1); _cursorX--; }
            else if (_cursorY > 0)
            {
                wstring currentLine = lines[_cursorY];

                lines.erase(lines.begin() + _cursorY);
                
                _cursorY--;
                _cursorX = lines[_cursorY].size();
                lines[_cursorY] += currentLine;
            } break;
        case 13:
        {
            lines.insert(lines.begin() + _cursorY + 1, lines[_cursorY].substr(_cursorX));
            lines[_cursorY] = lines[_cursorY].substr(0, _cursorX);

            _cursorY++;
            _cursorX = 0;
        } break;
        default:
        {
            if (key >= 32 && key <= 126)
            {
                if (lines[_cursorY].size() <= _cursorX) { lines[_cursorY].resize(_cursorX + 1, L' '); }

                lines[_cursorY].insert(_cursorX, 1, static_cast<wchar_t>(key));
                _cursorX++;
            }
            
            break;
        }
    }

    _content.clear();
    for (size_t i = 0; i < lines.size(); ++i) { _content += lines[i]; if (i != lines.size() - 1) _content += L'\n'; }
}

wstring TextEditor::getContent() const { return _content; }
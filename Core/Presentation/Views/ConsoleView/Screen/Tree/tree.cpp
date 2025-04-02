#include "../screen.h"
#include "../../consoleView.h"
#include "../../../../../Domain/domain.h"

using namespace Screen;

#define TREE_BRANCH L"\u251C\u2500\u2500 "
#define TREE_LAST_BRANCH L"\u2514\u2500\u2500 "
#define TREE_VERTICAL L"\u2502   "
#define TREE_INDENT L"    "

void drawCurrentDirectoryTree(const shared_ptr<Directory>& directory, int& x, int& y, bool consoleShowHidden)
{
    wstring directoryName = ConsoleView::toWString(directory->getName());

    if (consoleShowHidden || !directory->getIsHidden())
    {
        ConsoleView::gotoxy(x, y++);
        wcout << directoryName;

        const auto& contents = directory->getContents();
        for (size_t i = 0; i < contents.size(); i++)
        {
            const auto& unit = contents[i];
            bool last = (i == contents.size() - 1);

            if (consoleShowHidden || !unit->getIsHidden())
            {
                wstring unitName = ConsoleView::toWString(unit->getName());
                ConsoleView::gotoxy(x, y++);
                wcout << (last ? TREE_LAST_BRANCH : TREE_BRANCH) << unitName;
            }
        }
    }
}

wstring Tree::draw(const shared_ptr<Directory>& rootDirectory)
{
    ConfigParser _config(CONFIG_PATH);
    if (!_config.load()) { cerr << "Error: Cannot load the config" << endl; return L""; }
    bool padding = (_config.get("consolePadding") == "true");
    bool showHidden = (_config.get("consoleShowHidden") == "true");

    if (rootDirectory == nullptr)
    {
        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }
        ERROR("class Screen::Tree -> static method draw: rootDirectory is null!;"); throw invalid_argument("rootDirectory is null!");

        return L"";
    }
    int x = 32, y = (padding) ? 4 : 3;

    wstringstream stream;

    drawCurrentDirectoryTree(rootDirectory, x, y, showHidden);

    return stream.str();
}
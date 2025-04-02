#include "../../screen.h"
#include "../../../consoleView.h"

using namespace Screen;

void Updater::updateMessage(bool padding, const HeaderTypes& title, const wstring& message)
{
    switch (title)
    {
        case HeaderTypes::ErrorType: { localGoto(padding, 22, 2); wcout << L" ERROR "; } break;
        case HeaderTypes::SuccessfulType: { localGoto(padding, 22, 2); wcout << L"SUCCESS"; } break;
        case HeaderTypes::FillType:
        {
            mclear;

            vector<wstring> parts = ConsoleView::split(message, L'|');
            if (parts.size() < 2) { break; }

            wstring name = parts[0];
            wstring content = parts[1];

            Screen::TextEditor editor(name, content);
            bool saved = editor.edit();

            if (saved)
            {
                shared_ptr<Directory> currentDir = getData();
                vector<shared_ptr<Unit>>::iterator it = find_if(currentDir->getContents().begin(), currentDir->getContents().end(),
                    [&](const shared_ptr<Unit>& u) { return u->getName() == ConsoleView::wstringToString(name) && u->getFileType() == FileTypes::TextFileType; });

                if (it != currentDir->getContents().end())
                {
                    shared_ptr<AFile> file = dynamic_pointer_cast<AFile>(*it);

                    if (file)
                    {
                        file->editContent(ConsoleView::wstringToString(editor.getContent()));
                        file->setLastEditedDate(time(nullptr));
                        currentDir->setLastEditedDate(time(nullptr));
                    }
                }
            }

            update();
        } break;
        case HeaderTypes::PropType:
        {
            mclear;
            update();

            vector<wstring> properties;
            wstringstream stream(message);
            wstring property;

            while (getline(stream, property, L'|')) { properties.push_back(property); }

            for (int i = 0; i < properties.size(); i++)
            {
                if (padding) { ConsoleView::gotoxy(3, 6 + i); }
                else { ConsoleView::gotoxy(3, 5 + i); }
                wcout << properties.at(i);
            }
        } break;
        default: { localGoto(padding, 22, 2); wcout << L" ERROR "; } break;
    }

    if (title != HeaderTypes::PropType)
    {
        int maxIterator = ConsoleView::getTerminalSize().first;
        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); maxIterator -= (31 + 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); maxIterator -= (31 + 2); }

        wstringstream stream;
        for (int i = 0; i < maxIterator; i++) { stream << L' '; }
        wcout << stream.str();

        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }
        wcout << message;

        pause;
        update();
    }
}

void Updater::handleInput(Presenter& presenter, bool padding)
{
    while (!_exitFlag)
    {
        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }

        ViewModel viewModel = InputHandler::inputHandling(presenter);
        Updater::updateMessage(padding, viewModel.title, viewModel.message);

        if (_exitFlag) break;
    }
}

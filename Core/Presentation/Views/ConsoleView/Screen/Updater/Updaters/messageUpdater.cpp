#include "../../screen.h"

using namespace Screen;

void Updater::updateMessage(const HeaderTypes& title, const wstring& message)
{
    switch (title)
    {
        case HeaderTypes::ErrorType: { localGoto(22, 2); wcout << L" ERROR "; } break;
        case HeaderTypes::SuccessfulType: { localGoto(22, 2); wcout << L"SUCCESS"; } break;
        case HeaderTypes::FillType:
        {
            mclear;

            vector<wstring> parts = Tools::split(message, L'|');
            if (parts.size() < 2) { break; }

            wstring name = parts[0];
            wstring content = parts[1];

            Screen::TextEditor editor(name, content);
            bool saved = editor.edit();

            if (saved)
            {
                shared_ptr<Directory> currentDir = getData();
                vector<shared_ptr<Unit>>::iterator it = Tools::find(currentDir, Tools::wstringToString(name));

                if (it != currentDir->getContents().end())
                {
                    shared_ptr<AFile> file = dynamic_pointer_cast<AFile>(*it);

                    if (file)
                    {
                        file->editContent(Tools::wstringToString(editor.getContent()));
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
                if (_padding) { ConsoleView::gotoxy(3, 6 + i); }
                else { ConsoleView::gotoxy(3, 5 + i); }
                wcout << properties.at(i);
            }
        } break;
        case HeaderTypes::UpdateType:
        {
            update();
        } break;
        default: { localGoto( 22, 2); wcout << L" ERROR "; } break;
    }

    if (title != HeaderTypes::PropType && title != HeaderTypes::UpdateType)
    {
        int maxIterator = ConsoleView::getTerminalSize().first;
        if (_padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); maxIterator -= (31 + 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); maxIterator -= (31 + 2); }

        wstringstream stream;
        for (int i = 0; i < maxIterator; i++) { stream << L' '; }
        wcout << stream.str();

        if (_padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }
        wcout << message;

        pause;
        update();
    }
}

void Updater::handleInput(Presenter& presenter)
{
    while (!_exitFlag)
    {
        int inputX = _padding ? 32 : 31;
        int inputY = ConsoleView::getTerminalSize().second - (_padding ? 3 : 2);

        ConsoleView::gotoxy(inputX, inputY);

        ViewModel viewModel = InputHandler::inputHandling(presenter);
        Updater::updateMessage(viewModel.title, viewModel.message);

        if (_exitFlag) break;
    }
}
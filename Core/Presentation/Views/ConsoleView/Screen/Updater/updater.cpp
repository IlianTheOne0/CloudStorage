#include "../screen.h"
#include "../../consoleView.h"
#include "../../../../../Domain/domain.h"

using namespace Screen;

shared_mutex Updater::_consoleMutex;
atomic<bool> Updater::_exitFlag(false);
atomic<bool> Updater::_isStarted(false);
shared_ptr<Directory> Updater::_rootDirectory = nullptr;

void Updater::setData(const shared_ptr<Directory>& root) { _rootDirectory = root; }
shared_ptr<Directory> Updater::getData() { return _rootDirectory; }

bool Updater::getExitFlag() { return _exitFlag.load(); }
void Updater::setExitFlag(const bool& value) { _exitFlag = value; }

void Updater::redrawFrame(bool padding)
{
    while (!_exitFlag)
    {
        shared_lock<shared_mutex> lock(_consoleMutex);
        clear;
        wcout << Frame::draw();

        if (padding) { ConsoleView::gotoxy(6, 2); }
        else { ConsoleView::gotoxy(5, 1); }
        wcout << Clock::getCurrentDateTime();
        wcout << Tree::draw(_rootDirectory);

        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }

        sleep_for(seconds(60));
    }
}

void Updater::updateMessage(bool padding, const HeaderTypes& title, const wstring& message)
{
    switch (title)
    {
        case HeaderTypes::ErrorType:
        {
            if (padding) { ConsoleView::gotoxy(22, 2); }
            else { ConsoleView::gotoxy(21, 1); }
            wcout << L"ERROR";
        } break;

        case HeaderTypes::InputType:
        {
            if (padding) { ConsoleView::gotoxy(22, 2); }
            else { ConsoleView::gotoxy(21, 1); }
            wcout << L"WAITING";
        } break;

        case HeaderTypes::FillType:
        {
            if (padding) { ConsoleView::gotoxy(22, 2); }
            else { ConsoleView::gotoxy(21, 1); }
            wcout << L"FILLING";
        } break;

        case HeaderTypes::SuccessfulType:
        {
            if (padding) { ConsoleView::gotoxy(21, 2); }
            else { ConsoleView::gotoxy(20, 1); }
            wcout << L"SUCCESS";
        } break;

        default:
        {
            if (padding) { ConsoleView::gotoxy(22, 2); }
            else { ConsoleView::gotoxy(21, 1); }
            wcout << L"ERROR";
        }
    }

    if (padding) { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 3); }
    else { ConsoleView::gotoxy(30, ConsoleView::getTerminalSize().second - 2); }
    wcout << message;

    pause; update();
}

void Updater::handleInput(Presenter& presenter, bool padding)
{
    while (!_exitFlag)
    {
        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }

        ViewModel viewModel = InputHandler::inputHandling(presenter);
        Updater::updateMessage(padding, viewModel.title, viewModel.message);
    }
}

void Updater::start(Presenter& presenter)
{
    if (_isStarted.exchange(true)) { return; }

    clear;

    ConfigParser _config(CONFIG_PATH);
    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
    bool padding = (_config.get("consolePadding") == "true");

    thread redrawThread([padding]() { Updater::redrawFrame(padding); });
    thread inputThread([&presenter, padding]() { Updater::handleInput(presenter, padding); });

    redrawThread.detach();
    inputThread.join();
}

void Updater::update()
{
    ConfigParser _config(CONFIG_PATH);
    if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
    bool padding = (_config.get("consolePadding") == "true");

    clear;
    wcout << Frame::draw();
    wcout << Tree::draw(_rootDirectory);

    if (padding) { ConsoleView::gotoxy(6, 2); }
    else { ConsoleView::gotoxy(5, 1); }
    wcout << Clock::getCurrentDateTime();

    if (_exitFlag) { clear; }
}
#include "../screen.h"
#include "../../consoleView.h"
#include "../../../../../Domain/domain.h"

using namespace Screen;

shared_mutex Updater::_consoleMutex;
atomic<bool> Updater::_exitFlag(false);
atomic<bool> Updater::_isStarted(false);
shared_ptr<Directory> Updater::_rootDirectory = nullptr;
stack<shared_ptr<Directory>> Updater::_directoryStack;

void Updater::setData(const shared_ptr<Directory>& root, bool pushToStack)
{
    if (pushToStack && _rootDirectory) { _directoryStack.push(_rootDirectory); }
    _rootDirectory = root;
}

shared_ptr<Directory> Updater::getData() { return _rootDirectory; }

shared_ptr<Directory> Updater::getParentDirectory()
{
    if (!_directoryStack.empty()) { shared_ptr<Directory> parentDirectory = _directoryStack.top(); _directoryStack.pop(); return parentDirectory; }
    return nullptr;
}

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
        if (_exitFlag) break;

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

    pause;
    update();
}

void Updater::handleInput(Presenter& presenter, bool padding)
{
    while (!_exitFlag) {
        if (padding) { ConsoleView::gotoxy(32, ConsoleView::getTerminalSize().second - 3); }
        else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }

        ViewModel viewModel = InputHandler::inputHandling(presenter);
        Updater::updateMessage(padding, viewModel.title, viewModel.message);

        if (_exitFlag) break;
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
        
    redrawThread.join();
    inputThread.join();

    shared_ptr<Directory> rootDirectory = getData();
    if (rootDirectory) { string serializedData = Serializer::serializeDirectory(rootDirectory.get()); DataSyncUseCase::setData(serializedData); }
}

void Updater::update()
{
    if (!_exitFlag) {
        ConfigParser _config(CONFIG_PATH);
        if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
        bool padding = (_config.get("consolePadding") == "true");

        clear;
        wcout << Frame::draw();
        wcout << Tree::draw(_rootDirectory);

        if (padding) { ConsoleView::gotoxy(6, 2); }
        else { ConsoleView::gotoxy(5, 1); }
        wcout << Clock::getCurrentDateTime();
    }
    else { clear; }
}
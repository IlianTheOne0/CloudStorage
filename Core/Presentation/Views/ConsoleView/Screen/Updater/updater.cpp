#include "../screen.h"
#include "../../consoleView.h"
#include "../../../../../Domain/domain.h"

using namespace Screen;

void localGoto(bool padding, int x, int y) { if (padding) { ConsoleView::gotoxy(x, y); } else { ConsoleView::gotoxy(x - 1, y - 1); } };

shared_mutex Updater::_consoleMutex;
atomic<bool> Updater::_exitFlag(false);
atomic<bool> Updater::_isStarted(false);
shared_ptr<Directory> Updater::_rootDirectory = nullptr;
stack<shared_ptr<Directory>> Updater::_directoryStack;
wstring Updater::_path = L"root\\";

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

        localGoto(padding, 6, 2);
        wcout << Clock::getCurrentDateTime();
        wcout << Tree::draw(_rootDirectory);

        localGoto(padding, 32, 2);
        Updater::updatePath(); wcout << _path;

        localGoto(padding, 32, ConsoleView::getTerminalSize().second - 3);
        if (_exitFlag) break;

        sleep_for(seconds(60));
    }
}

void Updater::updateMessage(bool padding, const HeaderTypes& title, const wstring& message)
{
    switch (title)
    {
        case HeaderTypes::ErrorType: { localGoto(padding, 22, 2); wcout << L"ERROR"; } break;
        case HeaderTypes::InputType: { localGoto(padding, 22, 2); wcout << L"WAITING"; } break;
        case HeaderTypes::FillType: { localGoto(padding, 22, 2); wcout << L"FILLING"; } break;
        case HeaderTypes::SuccessfulType: { localGoto(padding, 21, 2); wcout << L"SUCCESS"; } break;
        default: { localGoto(padding, 22, 2); wcout << L"ERROR"; }
    }

    int maxIterator = ConsoleView::getTerminalSize().first;
    if (padding) { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 3); maxIterator -= (31 + 2); }
    else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); maxIterator -= (31 + 2); }

    wstringstream stream;
    for (int i = 0; i < maxIterator; i++) { stream << L' '; }
    wcout << stream.str();

    if (padding) { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 3); }
    else { ConsoleView::gotoxy(31, ConsoleView::getTerminalSize().second - 2); }
    wcout << message;

    pause;
    update();
}

void Updater::handleInput(Presenter& presenter, bool padding)
{
    while (!_exitFlag)
    {
        localGoto(padding, 32, ConsoleView::getTerminalSize().second - 3);

        ViewModel viewModel = InputHandler::inputHandling(presenter);
        Updater::updateMessage(padding, viewModel.title, viewModel.message);

        if (_exitFlag) break;
    }
}

void Updater::updatePath()
{
    if (_rootDirectory)
    {
        const auto& directoryName = _rootDirectory->getName();
        wstring currentDirName(directoryName.begin(), directoryName.end());

        vector<wstring> pathElements;
        wstringstream stream(_path);
        wstring item;

        while (getline(stream, item, L'\\')) { if (!item.empty()) { pathElements.push_back(item); } }

        if (!pathElements.empty() && pathElements.back() == currentDirName) { return; }
        else if (pathElements.size() > 1 && pathElements[pathElements.size() - 2] == currentDirName) { pathElements.pop_back(); }
        else { pathElements.push_back(currentDirName); }

        wstring newPath;
        for (const wstring& elem : pathElements) { newPath += elem + L'\\'; }

        _path = newPath;
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
}

void Updater::update()
{
    if (!_exitFlag)
    {
        ConfigParser _config(CONFIG_PATH);
        if (!_config.load()) { throw runtime_error("class ConsoleView <- constructor: Cannot load the config"); }
        bool padding = (_config.get("consolePadding") == "true");

        clear;
        wcout << Frame::draw();
        wcout << Tree::draw(_rootDirectory);

        localGoto(padding, 32, 2);
        Updater::updatePath(); wcout << _path;

        localGoto(padding, 6, 2);
        wcout << Clock::getCurrentDateTime();
    }
    else { clear; }
}
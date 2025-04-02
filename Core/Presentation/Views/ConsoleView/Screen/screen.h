#ifndef PRESENTATION_SCREEN_H
#define PRESENTATION_SCREEN_H

#include "../../../../Domain/domain.h"
#include "../../../../../Infrastructure/Config/presentationConfig.h"

#define WAITING_WSTR L"WAITING"
#define UODATE_DELEY 60

class Presenter;
namespace Screen
{
    class Updater
    {
    private:
        static shared_mutex _consoleMutex;
        static atomic<bool> _exitFlag;
        static atomic<bool> _isStarted;
        static shared_ptr<Directory> _rootDirectory;
        static stack<shared_ptr<Directory>> _directoryStack;
        static wstring _path;

        static void localGoto(bool padding, int x, int y);

        static void redrawFrame(bool padding);
        static void updateMessage(bool padding, const HeaderTypes& title, const wstring& message);
        static void handleInput(Presenter& presenter, bool padding);
        static void updatePath();
    public:
        static void setData(const shared_ptr<Directory>& root, bool pushToStack = true);
        static shared_ptr<Directory> getParentDirectory();
        static shared_ptr<Directory> getData();

        static bool getExitFlag();
        static void setExitFlag(const bool& value);

        static void start(Presenter& presenter);
        static void update();
    };

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

    class InputHandler
    {
    public:
        static ViewModel inputHandling(Presenter& presenter);
    };

    class Tree
    {
    public:
        static wstring draw(const shared_ptr<Directory>& rootDirectory);
    };

    class TextEditor
    {
    private:
        wstring _name;
        wstring _content;
        int _cursorX;
        int _cursorY;
        int _scrollOffset;

        void display();
        void processKeyPress(int key);
        void showCursor(bool visible);
    public:
        TextEditor(const wstring& filename, const wstring& content);
        
        bool edit();
        wstring getContent() const;
    };

    class ConstTextUpdater
    {
    public:
        static void update();
    };
}

#endif
#ifndef PRESENTATION_SCREEN_H
#define PRESENTATION_SCREEN_H

#include "../../../../Domain/domain.h"
#include "../../../../../Infrastructure/Config/presentationConfig.h"

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

        static void redrawFrame(bool padding);
        static void updateMessage(bool padding, const HeaderTypes& title, const wstring& message);
        static void handleInput(Presenter& presenter, bool padding);
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
}

#endif
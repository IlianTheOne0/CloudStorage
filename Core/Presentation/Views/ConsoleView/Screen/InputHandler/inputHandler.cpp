#include "../screen.h"
#include "../../consoleView.h"

using namespace Screen;

ViewModel InputHandler::inputHandling(Presenter& presenter)
{
    wstring userInput;

    if (wcin.peek() != EOF)
    {
        getline(wcin, userInput);
        return presenter.handle(userInput);
    }
    
    return ViewModel{HeaderTypes::NoneType, L""};
}
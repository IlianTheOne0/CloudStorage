#include "pathReceiver.h"

string PathReceiver::globalPath()
{
    path execPath = current_path();
    return execPath.string() + "\\";
}
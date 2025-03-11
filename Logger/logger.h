#ifndef LOGGER_H
#define LOGGER_H

#include "../Libs/LoggerConfig/loggerConfig.h"

class Logger
{
protected:
    static bool _isEnabled;

    static const unsigned short _info = 9;
    static const unsigned short _error = 12;
    static const unsigned short _warning = 14;
    static const unsigned short _default = 7;

public:
    static void log(string message, LoggerTypes loggerType = LoggerTypes::DefaultLogger, ConsoleColors color = ConsoleColors::DefaultColor);
    static bool getLoggerState();
    static void setLoggerState(const bool& state);
};

#endif
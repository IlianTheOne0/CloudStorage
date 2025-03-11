#ifndef MAIN_CONFIG_H
#define MAIN_CONFIG_H

#include "../Logger/logger.h"
#include "../Core/Data/ConfigParser/configParser.h"

using std::cerr;

#define CREATE_INFO(message) Logger::log(message, InfoADD)
#define INFO(message) Logger::log(message, Info)
#define ERROR(message) Logger::log(message, Error)
#define WARNING(message) Logger::log(message, Warning)
#define LOG_DEFAULT(message) Logger::log(message, DefaultLogger)
#define LOG_OWN(message, color) Logger::log(message, Own, color)

#define CONFIG_PATH "Libs/config.ini"

#endif
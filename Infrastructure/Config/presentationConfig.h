#ifndef PRESENTATION_CONFIG_H
#define PRESENTATION_CONFIG_H

#include "mainConfig.h"

#include <exception>
#include <sstream>
#include <Windows.h>
#include <iomanip>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <future>

using std::wstring;
using std::runtime_error;
using std::wstringstream;
using std::wcout;
using std::setw;
using std::setfill;
using std::chrono::time_point;
using std::chrono::system_clock;
using std::time_t;
using std::tm;
using std::put_time;
using std::async;
using std::launch;
using std::thread;
using std::this_thread::sleep_for;
using std::chrono::seconds;

#endif
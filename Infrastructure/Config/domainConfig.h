#ifndef DOMAIN_CONFIG_H
#define DOMAIN_CONFIG_H

#include "mainConfig.h"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

using std::string;
using std::wstring;
using std::to_string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::exception;
using std::invalid_argument;
using std::runtime_error;
using std::chrono::system_clock;
using std::ostringstream;
using std::wstringstream;
using std::put_time;

#endif
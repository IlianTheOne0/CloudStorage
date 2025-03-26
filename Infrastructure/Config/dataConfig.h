#ifndef DATA_CONFIG_H
#define DATA_CONFIG_H

#include "mainConfig.h"

#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>
#include <filesystem>
#include <memory>

using std::fstream;
using std::ofstream;
using std::streamsize;
using std::runtime_error;
using std::ios;
using std::filesystem::canonical;
using std::filesystem::exists;
using std::unique_ptr;
using std::make_unique;

#endif
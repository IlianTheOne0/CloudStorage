#ifndef SERVICES_CONFIG_H
#define SERVICES_CONFIG_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <memory>
#include <algorithm>
#include <random>
#include <array>
#include <iomanip>
#include <vector>
#include <exception>
#include <chrono>

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::ifstream;
using std::istringstream;
using std::stringstream;
using std::ofstream;
using std::forward;
using std::filesystem::path;
using std::filesystem::current_path;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::swap;
using std::copy;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::array;
using std::hex;
using std::setw;
using std::setfill;
using std::vector;
using std::domain_error;

#define DEFAULT_VALUE ""

#endif
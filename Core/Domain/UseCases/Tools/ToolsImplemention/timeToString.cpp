#include "../tools.h"
#include "../../../../../Infrastructure/Config/domainConfig.h"

string Tools::timeToString(const time_t& time)
{
    tm tm_struct;
    localtime_s(&tm_struct, &time);
    ostringstream oss;

    oss << put_time(&tm_struct, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}
#include "RoutingNumberGenerator.h"
#include <ctime>
#include <sstream>
#include <iomanip>

std::string RoutingNumberGenerator::generateRoutingNumber() {
    long now = static_cast<long>(std::time(nullptr));
    long nearestQuarterMinute = (now / 15) * 15 % 1000000000;
    std::ostringstream oss;
    oss << std::setw(9) << std::setfill('0') << nearestQuarterMinute;
    return oss.str();
}
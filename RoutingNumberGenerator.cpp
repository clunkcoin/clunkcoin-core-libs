#include "RoutingNumberGenerator.h"
#include <ctime>
#include <sstream>
#include <iomanip>

void RoutingNumberGenerator::generateRoutingNumber(std::string& routing_number) {
    time_t t = time(nullptr);
    long timestamp = static_cast<long>(t);
    long roundedTimestamp = (timestamp / 15) * 15;

    std::stringstream ss;
    ss << std::setw(9) << std::setfill('0') << (roundedTimestamp % 1000000000);
    routing_number = ss.str();
}

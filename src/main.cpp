#include "IpFilter.h"
#include <iostream>
#include <string>
#include <vector>

namespace Homework {

    const char TAB_CHARACTER = '\t';
    const char IP_DELIMITER = '.';
    const int NUMBER_OF_IP_PARTS = 4;

    IpAddress convertStringToIpAddress(const std::string& ipAsString) {
        IpAddress ipAddress;
        size_t startIndex = 0;
        for (size_t i = 0; i < NUMBER_OF_IP_PARTS; ++i) {
            size_t delimiterIndex = ipAsString.find_first_of('.', startIndex);
            std::string part = ipAsString.substr(startIndex, delimiterIndex);
            ipAddress[i] = std::stoi(part);
            startIndex = delimiterIndex + 1;
        }
        return ipAddress;
    }

    std::vector<IpAddress> readIpAddressesFromInput() {
        std::vector<IpAddress> ipAddresses;
        std::string line;
        while (std::getline(std::cin, line)) {
            std::string ipAsString = line.substr(0, line.find_first_of(TAB_CHARACTER));
            ipAddresses.push_back(convertStringToIpAddress(ipAsString));
        }
        return ipAddresses;
    }

    std::string convertIpAddressToString(const IpAddress& ipAddress) {
        return std::to_string(ipAddress[0]) 
            + IP_DELIMITER + std::to_string(ipAddress[1]) 
            + IP_DELIMITER + std::to_string(ipAddress[2]) 
            + IP_DELIMITER + std::to_string(ipAddress[3]);
    }
}

int main() {
    auto ipAddresses = Homework::readIpAddressesFromInput();
    auto filteredIpAddresses = Homework::filterIpAddresses(ipAddresses);
    
    for (const auto& ipAddress : filteredIpAddresses) {
        std::cout << Homework::convertIpAddressToString(ipAddress) << std::endl;
    }
    return 0;
}
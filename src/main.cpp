#include <iostream>
#include <string>
#include "IpFilter.h"

int main() {
    std::vector<std::string> ipAddresses;
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        ipAddresses.push_back(line.substr(0, line.find_first_of('\t')));
    }
    std::vector<std::string> filteredIps = Homework::filterIpAddresses(ipAddresses);
    for (const std::string& ip : filteredIps) {
        std::cout << ip << std::endl;
    }

    return 0;
}
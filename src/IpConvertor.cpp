#include "IpConvertor.h"

namespace Homework {
    const int IP_MAX_VALUE = 255;
    const char IP_DELIMITER = '.';
    const size_t IP_NUMBER_OF_DELIMITERS = 3;

    int parseIpPart(const std::string& ipPart) {
        int result;
        try {
            result = std::stoi(ipPart);
        } catch (...) {
            throw IpAddressParsingException(ipPart + " must be an integer number.");
        }
        if (result < 0 || result > IP_MAX_VALUE) {
            throw IpAddressParsingException(ipPart + " is out of range [0..255].");
        }
        return result;
    }

    IpAddress convertStringToIpAddress(const std::string& ipAsString) {
        auto numberOfDelimiters = std::count(ipAsString.begin(), ipAsString.end(), IP_DELIMITER);
        if (numberOfDelimiters != IP_NUMBER_OF_DELIMITERS) {
            throw IpAddressParsingException("The IP contains wrong number (" + std::to_string(numberOfDelimiters) + ") of dots.");
        }

        IpAddress ipAddress;
        size_t startIndex = 0;
        for (size_t i = 0; i < ipAddress.size() - 1; ++i) {
            size_t delimiterIndex = ipAsString.find_first_of(IP_DELIMITER, startIndex);
            ipAddress[i] = parseIpPart(ipAsString.substr(startIndex, delimiterIndex - startIndex));
            startIndex = delimiterIndex + 1;
        }
        ipAddress[ipAddress.size() - 1] = parseIpPart(ipAsString.substr(startIndex));
        return ipAddress;
    }
}
#include "IpFilter.h"
#include <array>
#include <algorithm>
#include <iterator>

namespace Homework {
    using IpAddress = std::array<int, 4>;
    
    const char IP_DELIMITER = '.';
    const int NUMBER_OF_IP_PARTS = 4;

    std::vector<IpAddress> convertIpsToNumericFormat(const std::vector<std::string>& ipAddresses) {
        std::vector<IpAddress> ipsAsNumeric;
        for (const std::string& ipAsString : ipAddresses) {
            IpAddress result;
            size_t startIndex = 0;
            for (size_t i = 0; i < NUMBER_OF_IP_PARTS; ++i) {
                size_t delimiterIndex = ipAsString.find_first_of('.', startIndex);
                std::string part = ipAsString.substr(startIndex, delimiterIndex);
                result[i] = std::stoi(part);
                startIndex = delimiterIndex + 1;
            }
            ipsAsNumeric.push_back(result);
        }
        return ipsAsNumeric;
    }

    std::string convertIpsToString(const IpAddress& ipAddress) {
        return std::to_string(ipAddress[0]) 
            + IP_DELIMITER + std::to_string(ipAddress[1]) 
            + IP_DELIMITER + std::to_string(ipAddress[2]) 
            + IP_DELIMITER + std::to_string(ipAddress[3]);
    }

    /// @brief creates a comparator which returns TRUE if the LEFT IP address is greater than the RIGHT one.
    /// @return a lambda expression which can be used as comparator in std::sort().
    auto createIpAddressComparator() {
        return [](IpAddress& l, IpAddress& r) {
            for (size_t i = 0; i < l.size(); ++i) {
                if (l[i] != r[i]) {
                    return l[i] > r[i];
                }
            }
            return false;
        };
    }

    void appendIpAddresses(std::vector<std::string>& output, const std::vector<IpAddress>& ipAddresses) {
        for (const IpAddress& ipAddress : ipAddresses) {
            output.push_back(convertIpsToString(ipAddress));
        }
    }

    std::vector<IpAddress> filter(const std::vector<IpAddress>& ipAddresses, int ipPart1) {
        std::vector<IpAddress> result;
        std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(result), [ipPart1](const IpAddress& x) { return x[0] == ipPart1; });
        return result;
    }

    std::vector<IpAddress> filter(const std::vector<IpAddress>& ipAddresses, int ipPart1, int ipPart2) {
        std::vector<IpAddress> result;
        std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(result), [ipPart1, ipPart2](const IpAddress& x) { 
            return x[0] == ipPart1 && x[1] == ipPart2; 
        });
        return result;
    }

    std::vector<IpAddress> filterAny(const std::vector<IpAddress>& ipAddresses, int ipPart) {
        std::vector<IpAddress> result;
        std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(result), [ipPart](const IpAddress& x) {
            for (int part : x) {
                if (part == ipPart) {
                    return true;
                }
            }
            return false;
        });
        return result;
    }

    std::vector<std::string> filterIpAddresses(const std::vector<std::string>& ipAddresses) {
        std::vector<IpAddress> ipsAsNumeric = convertIpsToNumericFormat(ipAddresses);
        //sort the IP list
        std::sort(ipsAsNumeric.begin(), ipsAsNumeric.end(), createIpAddressComparator());
        std::vector<std::string> result;
        appendIpAddresses(result, ipsAsNumeric);

        //find IPs which matches "1.x.x.x"
        std::vector<IpAddress> filteredIps = filter(ipsAsNumeric, 1);
        appendIpAddresses(result, filteredIps);

        //find IPs which matches "46.70.x.x"
        filteredIps = filter(ipsAsNumeric, 46, 70);
        appendIpAddresses(result, filteredIps);
        
        //find IPs with any byte equals to 46
        filteredIps = filterAny(ipsAsNumeric, 46);
        appendIpAddresses(result, filteredIps);
        return result;
    }
}
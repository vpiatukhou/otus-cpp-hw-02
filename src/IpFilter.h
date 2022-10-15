#pragma once

#include <array>
#include <vector>

namespace Homework {

    using IpAddress = std::array<int, 4>;

    std::vector<IpAddress> filter(const std::vector<IpAddress>& ipAddresses, int ipPart1);

    std::vector<IpAddress> filter(const std::vector<IpAddress>& ipAddresses, int ipPart1, int ipPart2);

    std::vector<IpAddress> filterAny(const std::vector<IpAddress>& ipAddresses, int ipPart);

    std::vector<IpAddress> filterIpAddresses(const std::vector<IpAddress>& ipAddresses);
};
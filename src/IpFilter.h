#pragma once

#include <array>
#include <vector>

namespace Homework {

    using IpAddress = std::array<int, 4>;

    std::vector<IpAddress> filterIpAddresses(const std::vector<IpAddress>& ipAddresses);
};
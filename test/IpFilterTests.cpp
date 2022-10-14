#include "IpFilter.h"
#include <gtest/gtest.h>

/// @brief tests all filter rules. We test all rules in the single test because they do not impact on each other. 
///                                Also we verify that filtered IP addresses are combined in the correct order.
TEST(FilterIpTest, filterIpAddresses) {
    //given
    std::vector<Homework::IpAddress> ipAddresses = { 
        //test filtering by 1.x.x.x
        {1, 1, 1, 1},
        {1, 2, 3, 4},
        {2, 1, 3, 4},
        {2, 3, 1, 4},
        {2, 3, 4, 1},
        {10, 2, 3, 4},
        {100, 2, 3, 4},
        //test filtering by 46.70.x.x
        {46, 70, 2, 2},
        {46, 70, 2, 2},
        {46, 2, 70, 2},
        {2, 70, 2, 2},
        //test filtering by 46.x.x.x or x.46.x.x or x.x.46.x or x.x.x.46
        {2, 2, 2, 46},
        {2, 2, 46, 2},
        {2, 46, 2, 2},
        {46, 2, 2, 2},
        {2, 2, 2, 2}
    };
    std::ostringstream out;

    //when
    auto result = Homework::filterIpAddresses(ipAddresses);
    //then
    std::vector<Homework::IpAddress> expected = {
        {100, 2, 3, 4},
        {46, 70, 2, 2},
        {46, 70, 2, 2},
        {46, 2, 70, 2},
        {46, 2, 2, 2},
        {10, 2, 3, 4},
        {2, 70, 2, 2},
        {2, 46, 2, 2},
        {2, 3, 4, 1},
        {2, 3, 1, 4},
        {2, 2, 46, 2},
        {2, 2, 2, 46},
        {2, 2, 2, 2},
        {2, 1, 3, 4},
        {1, 2, 3, 4},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 2, 3, 4},
        {46, 70, 2, 2},
        {46, 70, 2, 2},
        {46, 70, 2, 2},
        {46, 70, 2, 2},
        {46, 2, 70, 2},
        {2, 2, 2, 46},
        {2, 2, 46, 2},
        {2, 46, 2, 2},
        {46, 2, 2, 2}
    };

    EXPECT_EQ(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i], result[i]);
    }
}
//
// Created by toni on 02-02-23.
//

#include <gtest/gtest.h>

#include <string>
bool areEqual(const std::string& first, const std::string& second) { return first == second; }

TEST(HelloTest, IsGreeting) {
    std::string first{"Hello"};
    std::string second{"World"};
    EXPECT_PRED2(areEqual, first, second) << first << " and " << second << " are not equal strings";
}
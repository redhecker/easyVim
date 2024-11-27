#include "gtest/gtest.h"
#include "../modules/config.hpp"

TEST(TestSuite, Test_CALCULATE) {
  EXPECT_EQ(add(1, 1), 2);
}
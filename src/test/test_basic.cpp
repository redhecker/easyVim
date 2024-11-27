#include "gtest/gtest.h"

TEST(TestSuite, Test_1_plus_1) {
  EXPECT_EQ(1+1, 2);
}

TEST(TestSuite, TestEqual) {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(20, 20);
}
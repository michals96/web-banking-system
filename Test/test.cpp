#include "pch.h"
#include "../include/TestClass.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName1, TestName1) {
	TestClass testObject;

	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}
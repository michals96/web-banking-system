#include "pch.h"
#include "../include/TestClass.h"
#include "../src/TestClass.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestCaseName1, TestName1) {
	TestClass testObject;
	
	EXPECT_EQ(testObject.getStr(), "Hello World!");
	EXPECT_TRUE(true);
}
#include "pch.h"
#include "../include/TestClass.h"
#include "../src/TestClass.cpp"
#include "vs_google_test_explorer_namespace.h"

NAMESPACE_TEST(SimpleTests, TestClass, ifStringIsEqualDefaultValue)
{
	TestClass testObject;

	EXPECT_EQ(testObject.getStr(), "Hello World!");
	EXPECT_TRUE(true);
}

NAMESPACE_TEST(SimpleTests, TestClass, ifStringIsNotEmpty)
{
	TestClass testObject;

	EXPECT_NE(testObject.getStr(), "");
	EXPECT_TRUE(true);
}

NAMESPACE_TEST(SimpleTests, TestClass, ifStringIsProperlySet)
{
	TestClass testObject;
	testObject.setStr("Not a Hello World!");

	EXPECT_EQ(testObject.getStr(), "Not a Hello World!");
	EXPECT_TRUE(true);
}

// bierz dwoch userow i posprawdzaj cos na nich ->  niezerowe imie, nieujemny stan konta, konkretny stan konta(addtobalance)
// topusers zwraca niepusty wektor
// transactions zwraca date
// przetestuj funkcje z session
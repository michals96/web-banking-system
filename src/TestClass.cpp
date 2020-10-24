#include "../include/TestClass.h"

TestClass::TestClass()
{
	str = "Hello World!"; 
}

std::string TestClass::getStr()
{ 
	return str; 
}

void TestClass::setStr(std::string _str)
{ 
	str = _str; 
}

#include "log.h"
#include <iostream>

void Log::Print(const char* msg)
{
	std::cout << msg << std::endl;
}

void Log::Print(const int msg)
{
	std::cout << msg << std::endl;
}

void Log::Print(const float msg)
{
	std::cout << msg << std::endl;
}

void Log::Print(const GLubyte* msg)
{
	std::cout << msg << std::endl;
}


void Log::Error(const char* err)
{
	std::cerr << err << std::endl;
}

void Log::Error(const int msg)
{
	std::cerr << msg << std::endl;
}

void Log::Error(const float msg)
{
	std::cout << msg << std::endl;
}

void Log::Error(const GLubyte* err)
{
	std::cerr << err << std::endl;
}
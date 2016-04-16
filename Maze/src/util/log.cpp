#include "log.h"
#include <iostream>

void Log::print(const char* msg)
{
	std::cout << msg << std::endl;
}

void Log::print(const GLubyte* msg)
{
	std::cout << msg << std::endl;
}


void Log::error(const char* err)
{
	std::cerr << err << std::endl;
}

void Log::error(const GLubyte* err)
{
	std::cerr << err << std::endl;
}
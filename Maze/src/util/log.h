#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

class Log
{
public:
	static void print(const char* msg);
	static void print(const GLubyte* msg);

	static void error(const char* err);
	static void error(const GLubyte* err);
};
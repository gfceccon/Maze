#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

class Log
{
public:
	static void Print(const char* msg);
	static void Print(const int msg);
	static void Print(const float msg);
	static void Print(const GLubyte* msg);

	static void Error(const char* err);
	static void Error(const int msg);
	static void Error(const float msg);
	static void Error(const GLubyte* err);
};
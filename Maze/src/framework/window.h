#pragma once

#include <framework/game.h>

#define MAJOR_VERSION 3
#define MINOR_VERSION 1
#define ANTIALIASING_SAMPLES 4

class Window
{
	int width, height;
	GLFWwindow* window;
public:
	Window(const char* title, int width, int height);
	~Window();

	void start(Game* game);
	friend void errorCallback(int error, const char* description);
};

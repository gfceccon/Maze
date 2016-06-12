#pragma once

#include "scene.h"

#define MAJOR_VERSION 3
#define MINOR_VERSION 3
#define ANTIALIASING_SAMPLES 4

class Window
{
private:
	GLFWwindow* window;
	Scene* scene;
public:
	static int width;
	static int height;
	Window(const char* title);
	~Window();

	void setScene(Scene* scene);

	void start();
	friend void errorCallback(int error, const char* description);
};
void errorCallback(int error, const char* description);

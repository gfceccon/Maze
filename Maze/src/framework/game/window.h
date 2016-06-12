#pragma once

#include "scene.h"

#define MAJOR_VERSION 3
#define MINOR_VERSION 3
#define ANTIALIASING_SAMPLES 4

class Window
{
private:
	int width, height;
	GLFWwindow* window;
	Scene* scene;
	Scene* nextScene;
	bool shouldQuit = false;
public:
	Window(const char* title, int width, int height);
	~Window();

	void setScene(Scene* scene);
	void start();
	friend void errorCallback(int error, const char* description);
};

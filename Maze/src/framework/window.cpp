#include "window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <util/log.h>
#include <ctime>


Window::Window(const char* title, int width, int height)
{
	glfwSetErrorCallback(ErrorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING_SAMPLES);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);


	if (!window)
	{
		Log::Error("Failed to open GLFW window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	//If GLEW hasn't initialized  
	if (err != GLEW_OK)
	{
		Log::Error("Failed to open GLFW window");
		Log::Error(glewGetErrorString(err));
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	Log::Print("OpenGL version: ");
	Log::Print(glGetString(GL_VERSION));
	Log::Print("GLSL version: ");
	Log::Print(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

void Window::Start(Game* game)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window , MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetWindowPos(window, 50, 50);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);

	double time;
	double delta = glfwGetTime();

	do
	{
		glfwPollEvents();

		time = glfwGetTime();

		game->Update(static_cast<float>(delta));
		game->Draw(static_cast<float>(delta));

		glfwSwapBuffers(window);

		delta = glfwGetTime() - time;
		time = glfwGetTime();

		Log::Print(1.0f / (float)delta);

	} while (!glfwWindowShouldClose(window));
}


void ErrorCallback(int error, const char* description)
{
	Log::Error(description);
}
#include "window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <util/log.h>


Window::Window(const char* title, int width, int height)
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING_SAMPLES);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);


	if (!window)
	{
		Log::error("Failed to open GLFW window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();

	//If GLEW hasn't initialized  
	if (err != GLEW_OK)
	{
		Log::error("Failed to open GLFW window");
		Log::error(glewGetErrorString(err));
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	Log::print("OpenGL version: ");
	Log::print(glGetString(GL_VERSION));
	Log::print("GLSL version: ");
	Log::print(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

void Window::start(Game* game)
{
	glfwSetKeyCallback(window, keyCallback);
	glViewport(0, 0, width, height);

	do
	{
		glfwPollEvents();

		game->update();
		game->draw();

		glfwSwapBuffers(window);

	} while (!glfwWindowShouldClose(window));
}


void errorCallback(int error, const char* description)
{
	Log::error(description);
}
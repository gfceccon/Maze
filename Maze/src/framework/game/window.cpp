#include "window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../../util/log.h"

void errorCallback(int error, const char* description)
{
	Log::error(description);
}

Window::Window(const char* title, int width, int height)
{
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
	glfwWindowHint(GLFW_SAMPLES, ANTIALIASING_SAMPLES);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* pmonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(pmonitor);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwSetWindowPos(window, (vidmode->width - width)/2, (vidmode->height - height)/2);

	if (!window)
	{
		Log::error("Failed to open GLFW window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
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

void Window::setScene(Scene* scene)
{
	if (this->scene == nullptr)
		this->scene = scene;
	else
	{
		this->nextScene = scene;
		shouldQuit = true;
	}
}

void Window::start()
{
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window , mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, width, height);

	double time;
	double delta = glfwGetTime();
	do
	{
		do {
			glfwPollEvents();

			time = glfwGetTime();

			scene->update(static_cast<float>(delta));
			scene->draw(static_cast<float>(delta));

			glfwSwapBuffers(window);

			delta = glfwGetTime() - time;
			time = glfwGetTime();

		} while (!glfwWindowShouldClose(window) && !shouldQuit);

		if (nextScene != nullptr && !glfwWindowShouldClose(window))
		{
			scene = nextScene;
			shouldQuit = false;
		}
	} while (!shouldQuit);
}

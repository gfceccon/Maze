#include "window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../../util/log.h"

int Window::width = 0;
int Window::height = 0;

void errorCallback(int error, const char* description)
{
	Log::error(description);
}

#define WINDOW_X_OFFSET 0
#define WINDOW_Y_OFFSET 0

Window::Window(const char* title) : scene(nullptr), window(nullptr)
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
	glfwSetWindowPos(window, (vidmode->width - width) / 2 + WINDOW_X_OFFSET, (vidmode->height - height) / 2 + WINDOW_Y_OFFSET);

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
}

void Window::setScene(Scene* scene)
{
	if(this->scene == nullptr)
		this->scene = scene;
}

void Window::start()
{
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
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

		} while (!glfwWindowShouldClose(window) && !scene->shouldClose());
		Scene* current = scene;
		if (glfwWindowShouldClose(window))
			scene = nullptr;
		else if (scene->getNextScene() != nullptr)
			scene = scene->getNextScene();
		delete current;
	} while (scene != nullptr);
}

#include "scene.h"
#include <iostream>
#include "../../util/log.h"

std::queue<Event*> Scene::events;
bool Scene::key_states[1024];
Event* Scene::last_mouse = nullptr;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key != GLFW_KEY_UNKNOWN) {
		Scene::key_states[key] = action != GLFW_RELEASE;
		Scene::events.push(new Event(key, scancode, action, mods));
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float deltaX = 0;
	float deltaY = 0;

	if (Scene::last_mouse)
	{
		deltaX = static_cast<float>(xpos - Scene::last_mouse->x);
		deltaY = static_cast<float>(Scene::last_mouse->y - ypos);
		Scene::last_mouse->x = xpos;
		Scene::last_mouse->y = ypos;
	}
	else
		Scene::last_mouse = new Event(xpos, ypos);
	Scene::events.push(new Event(deltaX, deltaY));
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Scene::events.push(new Event(xoffset, yoffset, true));
}

Scene::Scene()
{
}

Scene::~Scene()
{
	if (last_mouse)
		delete last_mouse;
}

void Scene::update(float delta)
{
}

void Scene::draw(float delta)
{
	glClearColor(clear.r, clear.g, clear.b, clear.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

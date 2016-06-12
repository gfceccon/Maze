#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <queue>
#include "event.h"
#include "../../util/color.h"
#include "../../util/glm/vec3.hpp"
#include "../../util/glm/mat4x4.hpp"
#include "../../util/glm/gtc/matrix_transform.hpp"


class Scene
{
private:
	static Event* last_mouse;
	Scene* next;
	bool shouldQuit;
protected:
	Color clear = Color(0.0f, 0.0f, 0.0f);
	static std::queue<Event*> events;
	static bool key_states[1024];
	void close(Scene* next = nullptr);
public:
	Scene();
	virtual ~Scene();

	virtual void update(float delta);
	virtual void draw(float delta);

	bool shouldClose();
	Scene* getNextScene();

	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

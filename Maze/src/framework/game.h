#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "../util/color.h"

class Game
{
	Color clear;
public:
	Game();
	~Game();

	void setClearColor(Color& color);

	void update();
	void draw();
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


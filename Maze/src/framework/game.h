#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <util/color.h>
#include <framework/graphics/model/obj/square.h>
#include <framework/graphics/shader/shader.h>

class Game
{
	Color clear;
	Square* square;
	GLuint program;
	Shader* vertex_shader;
	Shader* frag_shader;
public:
	Game();
	~Game();

	void setClearColor(Color& color);

	void update();
	void draw();
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


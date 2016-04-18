#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

#include <framework/graphics/core/camera.h>
#include <util/color.h>
#include <framework/graphics/model/obj/cube.h>
#include <framework/graphics/shader/shader.h>

class Game
{
	Camera* camera;
	Color clear;
	GLuint program;
	Cube* cube;
	glm::mat4 cube_transf;
	Shader* vertex_shader;
	Shader* frag_shader;
public:
	Game(int width, int height);
	~Game();

	void setClearColor(Color& color);

	void update(float delta);
	void draw(float delta);
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


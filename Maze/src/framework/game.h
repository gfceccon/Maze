#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <queue>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

#include <maze/maze.h>
#include <maze/player.h>
#include <util/color.h>
#include <framework/event.h>
#include <framework/graphics/core/camera.h>
#include <framework/graphics/model/obj/cube.h>
#include <framework/graphics/shader/program.h>
#include <framework/graphics/shader/shader.h>

class Game
{
	Player* player;
	Camera* camera;
	Program* program;
	Maze* maze;
	Color clear;
	static Event* last_mouse;
	static std::queue<Event*> events;
	static bool key_states[1024];
	float move_sensibility = 2.5f, zoom_sensibility = .98f, rotation_sensibility = 25.0f;
public:
	Game(int width, int height);
	~Game();

	void setClearColor(Color& color);

	void update(float delta);
	void draw(float delta);

	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};


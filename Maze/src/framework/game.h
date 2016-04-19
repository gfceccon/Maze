#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <queue>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>

#include <maze/maze.h>
#include <util/color.h>
#include <framework/event.h>
#include <framework/graphics/core/camera.h>
#include <framework/graphics/model/obj/cube.h>
#include <framework/graphics/shader/program.h>
#include <framework/graphics/shader/shader.h>

class Game
{
	Camera* camera;
	Program* program;
	Maze* maze;
	Color clear;
	static Event* lastMouse;
	static std::queue<Event*> events;
	static bool keyStates[1024];
	float moveSensibility = 2.5f, zoomSensibility = .98f, rotationSensibility = 25.0f;
public:
	Game(int width, int height);
	~Game();

	void SetClearColor(Color& color);

	void Update(float delta);
	void Draw(float delta);

	friend void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	friend void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};


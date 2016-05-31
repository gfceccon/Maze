#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <queue>
#include "../util/glm/vec3.hpp"
#include "../util/glm/mat4x4.hpp"
#include "../util/glm/gtc/matrix_transform.hpp"

#include "../maze/maze.h"
#include "../maze/player.h"
#include "../util/color.h"
#include "event.h"
#include "graphics/core/camera.h"
#include "graphics/shader/program.h"
#include "graphics/shader/shader.h"
#include "graphics/effects/chrom_aberr.h"

class Game
{
	Player* player;
	Camera* camera;
	Program* program, *pp_program;
	Maze* maze;
	ChromAberr* aberr;
	Color clear = Color(1.0f, 1.0f, 1.0f);
	static Event* last_mouse;
	static std::queue<Event*> events;
	static bool key_states[1024];
    glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);
	float move_sensibility = 0.083f, zoom_sensibility = .98f, rotation_sensibility = 20.0f;
public:
	Game(int width, int height);
	~Game();

	void update(float delta);
	void draw(float delta);

	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

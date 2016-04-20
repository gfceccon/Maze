#pragma once

#include "../util/glm/vec3.hpp"
#include "maze.h"

enum Axis
{
	X, Y, Z
};

class Player
{
	friend class Camera;
	friend class Audio;

	glm::vec3 position;
	glm::vec3 front, up, right;
	const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
public:
	Player(glm::vec3 position = glm::vec3(0, 0, 0));
	~Player();

	void move(Maze* maze, Axis direction, float amount);
	void move(Maze* maze, float x, float y, float z);
};


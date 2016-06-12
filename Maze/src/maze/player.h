#pragma once

#include "../util/glm/vec3.hpp"
#include "maze.h"

#define sgn(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)

enum Axis
{
	X, Y, Z
};

class Player
{
	friend class Camera;
	friend class Audio;

    const float friction = 0.015f;
    glm::vec3 position;
    glm::vec3 front, up, right;
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 topVelocity = glm::vec3(2.5f, 2.5f, 2.5f);
	const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
public:
	Player(glm::vec3 position = glm::vec3(0, 0, 0));
	~Player();

    void applyVelocity(Axis direction, float amount);

	void move(Maze* maze, glm::vec3 gravity, float delta);
	void move(float x, float y, float z);
};


#include "player.h"

#include <util/log.h>

Player::Player(glm::vec3 position)
{
	this->position = position;
}


Player::~Player()
{
}

void Player::move(Maze* maze, Axis direction, float amount)
{
	glm::vec3 right = this->right;
	right.y = 0.0f;
	glm::vec3 front = this->front;
	front.y = 0.0f;
	glm::vec3 position;
	switch (direction)
	{
	case X:
		position = this->position + amount * right;
		break;
	case Y:
		position = this->position + amount * globalUp;
		break;
	case Z:
		position = this->position + amount * front;
	default:
		break;
	}
	maze->checkCollision(this->position, position);
	this->position = position;
}

void Player::move(Maze* maze, float x, float y, float z)
{
	glm::vec3 right = this->right;
	right.y = 0.0f;
	glm::vec3 front = this->front;
	front.y = 0.0f;

	position = position + x * right;
	position = position + y * globalUp;
	position = position + z * front;
}
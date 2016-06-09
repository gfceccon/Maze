#include "player.h"

#include "../util/log.h"

Player::Player(glm::vec3 position)
{
	this->position = position;
}

Player::~Player()
{
}

void Player::applyVelocity(Axis direction, float amount)
{
    switch (direction)
    {
    case X:
        velocity += amount * right;
        break;
    case Y:
        velocity += amount * globalUp;
        break;
    case Z:
        velocity += amount * front;
    default:
        break;
    }

    if (abs(velocity.x) > topVelocity.x)
        velocity.x = topVelocity.x * sgn(velocity.x);

    if (abs(velocity.y) > topVelocity.y)
        velocity.y = topVelocity.y * sgn(velocity.y);

    if (abs(velocity.z) > topVelocity.z)
        velocity.z = topVelocity.z * sgn(velocity.z);
}

void Player::move(Maze* maze, glm::vec3 gravity, float delta)
{
	glm::vec3 right = this->right;
	right.y = 0.0f;
	glm::vec3 front = this->front;
	front.y = 0.0f;
	glm::vec3 position;

    position = this->position + velocity * delta;

    if (position.y < 0.5f)
        position.y = 0.5f;

    if (position.y > 2.0f)
        position.y = 2.0f;

    velocity += gravity * delta;
    velocity -= abs(glm::length(velocity)) * friction * velocity;

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


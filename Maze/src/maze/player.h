#pragma once

#include <vec3.hpp>

class Player
{
	friend class Audio;
	glm::mediump_vec3 position;
	glm::mediump_vec3 front;
public:
	Player();
	~Player();
};


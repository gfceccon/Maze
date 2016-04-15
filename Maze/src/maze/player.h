#pragma once

#include "../util/vector3f.h"

class Player
{
	friend class Audio;
	Vector3f position;
	Vector3f front;
public:
	Player();
	~Player();
};


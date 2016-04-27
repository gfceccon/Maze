#pragma once

#include "timed_effectt.h"
#include "../../../util/glm/vec3.hpp"

class ChromAberr : public TimedEffect
{
	char *red_uniform, *green_uniform, *blue_uniform;
	glm::vec2 red_offset, green_offset, blue_offset;
	int width, height;
public:
	ChromAberr(int width, int height, Program* program);
	~ChromAberr();
	void init(char* red_uniform, glm::vec2 red_offset, char* green_uniform, glm::vec2 green_offset, char* blue_uniform, glm::vec2 blue_offset);
	void draw(float delta) override;
};


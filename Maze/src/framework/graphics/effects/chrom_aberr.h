#pragma once

#include "timed_effectt.h"
#include "../../../util/glm/vec3.hpp"

class ChromAberr : public TimedEffect
{
	const char *red_uniform, *green_uniform, *blue_uniform;
	glm::vec2 red_offset, green_offset, blue_offset;
	int width, height;
public:
	ChromAberr(int width, int height, Program* program);
	void init(const char* red_uniform, glm::vec2 red_offset, const char* green_uniform, glm::vec2 green_offset, const char* blue_uniform, glm::vec2 blue_offset);
	void draw(float delta) override;
};


#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"
#include "light.h"

#define DIRLIGHT_NAME "directional"

#define DIRLIGHT_DIRECTION "direction"

class DirectionalLight : public Light
{
private:
	glm::vec3 direction;
public:
	DirectionalLight(int index = -1, const char* name = DIRLIGHT_NAME);
	~DirectionalLight();

	void setDirection(float x, float y, float z);

	void bind(Program* program) override;
};


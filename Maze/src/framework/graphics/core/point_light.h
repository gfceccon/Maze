#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"
#include "light.h"

#define POINTLIGHT_NAME "light"

#define POINTLIGHT_POSITION "position"

#define POINTLIGHT_ATT_CONST "constant"
#define POINTLIGHT_ATT_LINEAR "linear"
#define POINTLIGHT_ATT_QUAD "quadratic"

class PointLight : public Light
{
private:
	glm::vec3 position;

	float attConstant;
	float attLinear;
	float attQuadratic;

public:

	PointLight(int index = -1);
	~PointLight();

	void setPosition(float x, float y, float z);

	void setAttenuation(float constant, float linear, float quadraditic);

	void bind(Program* program) override;
};


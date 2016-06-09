#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"

#define LIGHT_NAME "light"

#define LIGHT_POSITION "position"
#define LIGHT_AMBIENT "ambient"
#define LIGHT_DIFFUSE "diffuse"
#define LIGHT_SPECULAR "specular"

#define LIGHT_ATT_CONST "constant"
#define LIGHT_ATT_LINEAR "linear"
#define LIGHT_ATT_QUAD "quadratic"

class Light
{
private:
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float attConstant;
	float attLinear;
	float attQuadratic;

	int index;

	void setLightAttrString(std::string& str);
public:

	Light(int index = -1);
	~Light();

	void setPosition(float x, float y, float z);

	void setAmbient(float x, float y, float z);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);

	void setAttenuation(float constant, float linear, float quadraditic);

	void bind(Program* program);
};


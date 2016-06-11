#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"

#define LIGHT_NAME "light"

#define LIGHT_AMBIENT "ambient"
#define LIGHT_DIFFUSE "diffuse"
#define LIGHT_SPECULAR "specular"

class Light
{
protected:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	int index;

	void getLightAttrString(const char* light_name, std::string& str);
public:
	Light(int index = -1);
	~Light();

	void setAmbient(float x, float y, float z);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);

	virtual void bind(Program* program);
};


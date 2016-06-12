#pragma once

#include <GL/glew.h>
#include <string>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"

#define LIGHT_NAME "light"

#define LIGHT_AMBIENT "ambient"
#define LIGHT_DIFFUSE "diffuse"
#define LIGHT_SPECULAR "specular"

class Light
{
private:
	const char* name;
	std::string string;
protected:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;


	int index;

	const char* getAttribute(const char* attribute);
public:
	Light(int index = -1, const char* name = LIGHT_NAME);
	~Light();

	void setAmbient(float x, float y, float z);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);

	virtual void bind(Program* program);
};


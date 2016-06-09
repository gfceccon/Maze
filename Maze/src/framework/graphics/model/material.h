#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"

#define MATERIAL_NAME "material"

#define MATERIAL_AMBIENT "ambient"
#define MATERIAL_DIFFUSE "diffuse"
#define MATERIAL_SPECULAR "specular"

#define MATERIAL_SHININESS "shininess"

class Material
{
private:
	const char* name;
	std::string string;
	int index;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;

public:
	Material(const char* name = MATERIAL_NAME, int index = -1);
	~Material();

	const char* getAttribute(const char* attr);

	void setAmbient(float x, float y, float z);
	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);

	void setShininess(float shininess);

	void bind(Program* program);
};

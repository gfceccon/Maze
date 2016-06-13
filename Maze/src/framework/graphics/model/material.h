#pragma once

#include <GL/glew.h>
#include <string>
#include "../shader/program.h"
#include "../../../util/glm/vec3.hpp"
#include "../../../../soil/src/SOIL.h"

#define MATERIAL_NAME "material"

#define MATERIAL_DIFFUSE "diffuse"
#define MATERIAL_SPECULAR "specular"

#define MATERIAL_DIFFUSE_TEXTURE "diffuse2D"
#define MATERIAL_SPECULAR_TEXTURE "specular2D"
#define MATERIAL_NORMAL_TEXTURE "normal2D"
#define MATERIAL_DEPTH_TEXTURE "depth2D"
#define MATERIAL_AO_TEXTURE "occlusion2D"

#define MATERIAL_SHININESS "shininess"

class Material
{
private:
	const char* name;
	std::string string;
	int index;

	glm::vec3 diffuse;
	glm::vec3 specular;

	float shininess;

	GLuint diffuseTex, specularTex, normalTex, depthTex, occlusionTex;
	bool hasDiffuse, hasSpecular, hasNormal, hasDepth, hasOcclusion;
	void initImage(GLuint location, Program* program, const char* file_name);
	void bindTexture(Program* program, const char* textureAttribute, GLint& index, GLuint textureId);

public:

	enum TextureType
	{
		Diffuse,
		Specular,
		Normal,
		Depth,
		AmbientOcclusion
	};

	Material(int index = -1, const char* name = MATERIAL_NAME);
	~Material();

	const char* getAttribute(const char* attr);

	void setDiffuse(float x, float y, float z);
	void setSpecular(float x, float y, float z);

	void setShininess(float shininess);

	void initTexture(Program* program, const char* file_name, TextureType type);

	void bind(Program* program);
};

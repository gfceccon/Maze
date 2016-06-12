#include "material.h"



Material::Material(int index, const char* name) : index(index), name(name)
{
	setDiffuse(1.0f, 1.0f, 1.0f);
	setSpecular(1.0f, 1.0f, 1.0f);
	setShininess(10.0f);
}


Material::~Material()
{
	if (hasDiffuse)
		glDeleteTextures(1, &diffuseTex);
	if (hasSpecular)
		glDeleteTextures(1, &specularTex);
	if (hasNormal)
		glDeleteTextures(1, &normalTex);
	if (hasDepth)
		glDeleteTextures(1, &depthTex);
}

const char* Material::getAttribute(const char* attribute)
{
	string = name;
	if (index != -1)
	{
		string += "[";
		string += std::to_string(index);
		string += "]";
	}
	string += ".";
	string += attribute;

	return string.c_str();
}

void Material::setDiffuse(float x, float y, float z)
{
	this->diffuse.x = x;
	this->diffuse.y = y;
	this->diffuse.z = z;
}

void Material::setSpecular(float x, float y, float z)
{
	this->specular.x = x;
	this->specular.y = y;
	this->specular.z = z;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

void Material::bind(Program * program)
{
	GLint textureIndex = 0;

	if(hasDiffuse)
		bindTexture(program, getAttribute(MATERIAL_DIFFUSE_TEXTURE), textureIndex, diffuseTex);
	else
		program->setVec3(diffuse, getAttribute(MATERIAL_DIFFUSE));

	if(hasSpecular)
		bindTexture(program, getAttribute(MATERIAL_SPECULAR_TEXTURE), textureIndex, specularTex);
	else
		program->setVec3(specular, getAttribute(MATERIAL_SPECULAR));

	if(hasNormal)
		bindTexture(program, getAttribute(MATERIAL_NORMAL_TEXTURE), textureIndex, normalTex);

	if(hasDepth)
		bindTexture(program, getAttribute(MATERIAL_DEPTH_TEXTURE), textureIndex, depthTex);

	program->setFloat(shininess, getAttribute(MATERIAL_SHININESS));
}

void Material::bindTexture(Program* program, const char * textureAttribute, GLint & index, GLuint textureId)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, textureId);
	program->setInt(index, textureAttribute);
	index++;
}

void Material::initTexture(Program* program, const char* file_name, Material::TextureType type)
{
	switch (type)
	{
	case Material::Diffuse:
		if (!hasDiffuse)
			glGenTextures(1, &diffuseTex);
		initImage(diffuseTex, program, file_name);
		hasDiffuse = true;
		break;
	case Material::Specular:
		if (!hasSpecular)
			glGenTextures(1, &specularTex);
		initImage(specularTex, program, file_name);
		hasSpecular = true;
		break;
	case Material::Normal:
		if (!hasNormal)
			glGenTextures(1, &normalTex);
		initImage(normalTex, program, file_name);
		hasNormal = true;
		break;
	case Material::Depth:
		if (!hasDepth)
			glGenTextures(1, &depthTex);
		initImage(depthTex, program, file_name);
		hasDepth = true;
		break;
	default:
		break;
	}
}

void Material::initImage(GLuint location, Program* program, const char* file_name)
{
	glBindTexture(GL_TEXTURE_2D, location);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(file_name, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

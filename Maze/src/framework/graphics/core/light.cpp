#include "light.h"


Light::Light(int index, const char* name) : name(name), index(index)
{
	setAmbient(1.0f, 1.0f, 1.0f);
	setDiffuse(1.0f, 1.0f, 1.0f);
	setSpecular(1.0f, 1.0f, 1.0f);
}


Light::~Light()
{
}


void Light::setAmbient(float x, float y, float z)
{
	this->ambient.x = x;
	this->ambient.y = y;
	this->ambient.z = z;
}

void Light::setDiffuse(float x, float y, float z)
{
	this->diffuse.x = x;
	this->diffuse.y = y;
	this->diffuse.z = z;
}

void Light::setSpecular(float x, float y, float z)
{
	this->specular.x = x;
	this->specular.y = y;
	this->specular.z = z;
}

void Light::bind(Program * program)
{
	program->setVec3(ambient, getAttribute(LIGHT_AMBIENT));

	program->setVec3(diffuse, getAttribute(LIGHT_DIFFUSE));

	program->setVec3(specular, getAttribute(LIGHT_SPECULAR));
}

const char* Light::getAttribute(const char* attribute)
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

#include "light.h"


Light::Light(int index)
{
	this->index = index;
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
	std::string attribute;

	getLightAttrString(LIGHT_NAME, attribute);
	attribute += LIGHT_AMBIENT;
	program->setVec3(ambient, attribute.c_str());


	getLightAttrString(LIGHT_NAME, attribute);
	attribute += LIGHT_DIFFUSE;
	program->setVec3(diffuse, attribute.c_str());


	getLightAttrString(LIGHT_NAME, attribute);
	attribute += LIGHT_SPECULAR;
	program->setVec3(specular, attribute.c_str());
}

void inline Light::getLightAttrString(const char* light_name, std::string& string)
{
	string = light_name;
	if (index != -1)
	{
		string += "[";
		string += itoa(index, nullptr, 10);
		string += "]";
	}

	string += ".";
}

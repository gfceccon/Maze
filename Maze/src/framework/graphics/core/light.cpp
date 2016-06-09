#include "light.h"



Light::Light(int index) : index(index)
{
}


Light::~Light()
{
}

void Light::setPosition(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
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

void Light::setAttenuation(float constant, float linear, float quadraditic)
{
	this->attConstant = constant;
	this->attLinear = linear;
	this->attQuadratic = quadraditic;
}

void inline Light::setLightAttrString(std::string& string)
{
	string = LIGHT_NAME;
	if (index != -1)
	{
		string += "[";
		string += itoa(index, nullptr, 10);
		string += "]";
	}

	string += ".";
}

void Light::bind(Program * program)
{
	std::string string;

	setLightAttrString(string);
	string += LIGHT_POSITION;
	program->setVec3(position, string.c_str());


	setLightAttrString(string);
	string += LIGHT_AMBIENT;
	program->setVec3(ambient, string.c_str());


	setLightAttrString(string);
	string += LIGHT_DIFFUSE;
	program->setVec3(diffuse, string.c_str());


	setLightAttrString(string);
	string += LIGHT_SPECULAR;
	program->setVec3(specular, string.c_str());


	setLightAttrString(string);
	string += LIGHT_ATT_CONST;
	program->setFloat(attConstant, string.c_str());


	setLightAttrString(string);
	string += LIGHT_ATT_LINEAR;
	program->setFloat(attLinear, string.c_str());


	setLightAttrString(string);
	string += LIGHT_ATT_QUAD;
	program->setFloat(attQuadratic, string.c_str());
}

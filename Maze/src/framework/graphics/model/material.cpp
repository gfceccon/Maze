#include "material.h"



Material::Material(const char* name, int index) : name(name), index(index)
{
}


Material::~Material()
{
}

const char* Material::getAttribute(const char* attr)
{
	string = name;
	if (index >= 0)
	{
		string += "[";
		string += itoa(index, nullptr, 10);
		string += "]";
	}
	string += ".";
	string += attr;

	return string.c_str();
}

void Material::setAmbient(float x, float y, float z)
{
	this->ambient.x = x;
	this->ambient.y = y;
	this->ambient.z = z;
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
	std::string string;


	program->setVec3(ambient, getAttribute(MATERIAL_AMBIENT));

	program->setVec3(ambient, getAttribute(MATERIAL_DIFFUSE));

	program->setVec3(ambient, getAttribute(MATERIAL_SPECULAR));

	program->setFloat(shininess, getAttribute(MATERIAL_SHININESS));
}

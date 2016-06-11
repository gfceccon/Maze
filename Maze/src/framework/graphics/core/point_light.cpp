#include "point_light.h"



PointLight::PointLight(int index, const char* name) : Light(index, name)
{
}


PointLight::~PointLight()
{
}

void PointLight::setPosition(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void PointLight::setAttenuation(float constant, float linear, float quadraditic)
{
	this->attConstant = constant;
	this->attLinear = linear;
	this->attQuadratic = quadraditic;
}

void PointLight::bind(Program * program)
{
	Light::bind(program);
	
	program->setVec3(position, getAttribute(POINTLIGHT_POSITION));
	
	program->setFloat(attConstant, getAttribute(POINTLIGHT_ATT_CONST));
	
	program->setFloat(attLinear, getAttribute(POINTLIGHT_ATT_LINEAR));

	program->setFloat(attQuadratic, getAttribute(POINTLIGHT_ATT_QUAD));
}

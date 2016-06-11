#include "point_light.h"



PointLight::PointLight(int index) : Light(index)
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
	std::string attribute;

	getLightAttrString(POINTLIGHT_NAME, attribute);
	attribute += POINTLIGHT_POSITION;
	program->setVec3(position, attribute.c_str());


	getLightAttrString(POINTLIGHT_NAME, attribute);
	attribute += POINTLIGHT_ATT_CONST;
	program->setFloat(attConstant, attribute.c_str());


	getLightAttrString(POINTLIGHT_NAME, attribute);
	attribute += POINTLIGHT_ATT_LINEAR;
	program->setFloat(attLinear, attribute.c_str());


	getLightAttrString(POINTLIGHT_NAME, attribute);
	attribute += POINTLIGHT_ATT_QUAD;
	program->setFloat(attQuadratic, attribute.c_str());
}

#include "directional_light.h"

DirectionalLight::DirectionalLight(int index, const char * name) : Light(index, name)
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::setDirection(float x, float y, float z)
{
	direction.x = x;
	direction.y = y;
	direction.z = z;
}

void DirectionalLight::bind(Program * program)
{
	Light::bind(program);

	program->setVec3(direction, getAttribute(DIRLIGHT_DIRECTION));
}

#include "multiple_light.h"



MultipleLight::MultipleLight(unsigned int size)
{
}



MultipleLight::~MultipleLight()
{
}

void MultipleLight::clear()
{
	lights.clear();
}

void MultipleLight::addLight(Light* light)
{
	if (lights.size() < size)
		lights.push_back(light);
}

void MultipleLight::bind(Program * program)
{
	program->setInt(lights.size(), LIGHTS_SIZE);
	for each (Light* light in lights)
		light->bind(program);
}

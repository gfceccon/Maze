#pragma once

#include <vector>
#include "light.h"

#define LIGHTS_SIZE "lightsSize"

class MultipleLight
{
private:
	std::vector<Light*> lights;
	unsigned int size;
public:
	MultipleLight(unsigned int size);
	~MultipleLight();

	void clear();
	void addLight(Light* light);

	void bind(Program* program);
};


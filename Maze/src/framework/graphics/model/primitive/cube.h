#pragma once

#include <framework/graphics/model/simple_model.h>

class Cube : public SimpleModel
{
	const GLsizei nvert = 36;
public:
	Cube();
	~Cube();
	void draw() override;
	void bind() override;
};


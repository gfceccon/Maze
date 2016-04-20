#pragma once

#include <framework/graphics/model/simple_model.h>

class Square : public SimpleModel
{
	const GLsizei nvert = 12, nind = 6;
public:
	Square();
	~Square();
	void draw() override;
	void bind() override;
};


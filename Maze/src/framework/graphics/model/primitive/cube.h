#pragma once

#include "../simple_model.h"
#include "../../shader/program.h"

class Cube : public SimpleModel
{
public:
	Cube(Program* program, const char* tex_fname);
	~Cube();
	void draw() override;
};


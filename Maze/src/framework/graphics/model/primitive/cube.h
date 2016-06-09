#pragma once

#include "../model.h"
#include "../../shader/program.h"

class Cube : public Model
{
public:
	Cube(Program* program, const char* tex_fname = nullptr);
	~Cube();
	void draw() override;
};


#pragma once

#include "../simple_model.h"
#include "../../shader/program.h"

class Square : public SimpleModel
{
public:
	Square(Program* program, const char* tex_fname = nullptr);
	~Square();
	void draw() override;
};


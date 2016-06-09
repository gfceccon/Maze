#pragma once

#include "../model.h"
#include "../../shader/program.h"

class Square : public Model
{
public:
	Square(Program* program, const char* tex_fname = nullptr);
	~Square();
	void draw() override;
};


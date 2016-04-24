#pragma once

#include "../simple_model.h"
#include "../../shader/program.h"

class Square : public SimpleModel
{
public:
	Square(Program* program);
	~Square();
	void draw() override;
};


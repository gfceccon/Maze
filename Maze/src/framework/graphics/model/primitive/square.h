#pragma once

#include "../model.h"
#include "../../shader/program.h"

class Square : public Model
{
public:
	Square(Program* program);
	~Square();
};


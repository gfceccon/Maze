#pragma once

#include "../model.h"
#include "../../shader/program.h"

class Quad : public Model
{
public:
	Quad(Program* program);
	~Quad();
};


#pragma once

#include "../model.h"
#include "../../shader/program.h"

class AdvancedCube : public Model
{
public:
	AdvancedCube(Program* program, const char* tex_fname = nullptr, const char* normalmap_fname = nullptr, const char* depthmap_fname = nullptr);
	~AdvancedCube();

	void draw() override;
};


#include "advanced_cube.h"



AdvancedCube::AdvancedCube(Program* program)
{
	Model::nvertices = 36;
	Model::vertices = new GLfloat[nvertices * 3]{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 0.0f,  1.0f,
		1.0f, 0.0f,  1.0f,
		1.0f, 1.0f,  1.0f,
		1.0f, 1.0f,  1.0f,
		0.0f, 1.0f,  1.0f,
		0.0f, 0.0f,  1.0f,

		0.0f,  1.0f,  1.0f,
		0.0f,  1.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
		0.0f,  0.0f, 0.0f,
		0.0f,  0.0f, 1.0f,
		0.0f,  1.0f, 1.0f,

		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, 0.0f,
		1.0f,  0.0f, 0.0f,
		1.0f,  0.0f, 0.0f,
		1.0f,  0.0f, 1.0f,
		1.0f,  1.0f, 1.0f,

		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,

		0.0f,  1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		0.0f,  1.0f,  1.0f,
		0.0f,  1.0f, 0.0f
	};
	Model::uvs = new GLfloat[nvertices * 2]{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
}


AdvancedCube::~AdvancedCube()
{
}

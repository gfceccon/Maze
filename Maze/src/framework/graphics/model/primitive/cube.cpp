#include "cube.h"

Cube::Cube(Program* program)
{
	SimpleModel::nvertices = 36;
	SimpleModel::vertices = new GLfloat[nvertices * 3]{
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
	SimpleModel::uvs = new GLfloat[nvertices * 2]{
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
	SimpleModel::indices = nullptr;
	SimpleModel::colors = nullptr;
	SimpleModel::initTexture(program, "resources/arrow.jpg");
	SimpleModel::init(program, GL_STATIC_DRAW);
}


Cube::~Cube()
{
}

void Cube::draw()
{
	SimpleModel::draw(GL_TRIANGLES);
}
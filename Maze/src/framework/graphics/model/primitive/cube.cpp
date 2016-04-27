#include "cube.h"

Cube::Cube(Program* program, const char* tex_fname)
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
	if(tex_fname)
		SimpleModel::initTexture(program, tex_fname);
	SimpleModel::init(program, GL_STATIC_DRAW);
}


Cube::~Cube()
{
}

void Cube::draw()
{
	SimpleModel::draw(GL_TRIANGLES);
}
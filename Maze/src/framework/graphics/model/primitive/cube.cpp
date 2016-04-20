#include "cube.h"



Cube::Cube()
{
	SimpleModel::vertices = new GLfloat[nvert * 3]{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 
		1.0f,  1.0f, 0.0f, 
		1.0f,  1.0f, 0.0f, 
		0.0f,  1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,

		0.0f, 0.0f,  1.0f,
		1.0f, 0.0f,  1.0f, 
		1.0f,  1.0f,  1.0f, 
		1.0f,  1.0f,  1.0f, 
		0.0f,  1.0f,  1.0f,
		0.0f, 0.0f,  1.0f,

		0.0f,  1.0f,  1.0f,
		0.0f,  1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f,  1.0f,
		0.0f,  1.0f,  1.0f,

		1.0f,  1.0f,  1.0f, 
		1.0f,  1.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f,  1.0f, 
		1.0f,  1.0f,  1.0f, 

		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f,  1.0f, 
		1.0f, 0.0f,  1.0f, 
		0.0f, 0.0f,  1.0f,
		0.0f, 0.0f, 0.0f,

		0.0f,  1.0f, 0.0f,
		1.0f,  1.0f, 0.0f, 
		1.0f,  1.0f,  1.0f, 
		1.0f,  1.0f,  1.0f, 
		0.0f,  1.0f,  1.0f,
		0.0f,  1.0f, 0.0f
	};
	SimpleModel::indices = nullptr;
	SimpleModel::normals = nullptr;
	SimpleModel::nvertices = nvert;
	SimpleModel::init();
}


Cube::~Cube()
{
}

void Cube::draw()
{
	SimpleModel::draw(GL_TRIANGLES);
}

void Cube::bind()
{
	SimpleModel::bind(GL_STATIC_DRAW);
}

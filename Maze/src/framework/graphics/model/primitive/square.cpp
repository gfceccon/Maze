#include "square.h"



Square::Square()
{
	SimpleModel::vertices = new GLfloat[nvert]
	{
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	SimpleModel::indices = new GLuint[nind]
	{
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	SimpleModel::normals = nullptr;
	SimpleModel::nvertices = nvert;
	SimpleModel::nindices = nind;
	SimpleModel::init();
}


Square::~Square()
{
}

void Square::draw()
{
	SimpleModel::draw(GL_TRIANGLES);
}

void Square::bind()
{
	SimpleModel::bind(GL_STATIC_DRAW);
}
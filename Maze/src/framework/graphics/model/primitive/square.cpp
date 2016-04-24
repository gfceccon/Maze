#include "square.h"



Square::Square(Program* program)
{
	SimpleModel::nvertices = 4;
	SimpleModel::nindices = 2;
	SimpleModel::vertices = new GLfloat[nvertices * 3]
	{
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};
	SimpleModel::indices = new GLuint[nindices * 3]
	{
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	SimpleModel::uvs = nullptr;
	SimpleModel::colors = nullptr;
	SimpleModel::init(program, GL_STATIC_DRAW);
}


Square::~Square()
{
}

void Square::draw()
{
	SimpleModel::draw(GL_TRIANGLES);
}
#include "square.h"



Square::Square(Program* program, const char* tex_fname)
{
	SimpleModel::nvertices = 6;
	//SimpleModel::nindices = 2;
	SimpleModel::vertices = new GLfloat[nvertices * 3]
	{
		 1.0f, -1.0f, 0.0f,  // Bottom Right
		 1.0f,  1.0f, 0.0f,  // Top Right
		-1.0f,  1.0f, 0.0f,  // Top Left 
		-1.0f, -1.0f, 0.0f,  // Bottom Left
		 1.0f, -1.0f, 0.0f,  // Bottom Right
		-1.0f,  1.0f, 0.0f   // Top Left 
	};
	SimpleModel::indices = nullptr;
	//SimpleModel::indices = new GLuint[nindices * 3]
	//{
	//	0, 1, 3,  // First Triangle
	//	1, 2, 3   // Second Triangle
	//};
	SimpleModel::uvs = new GLfloat[nvertices * 2]
	{
		1, 0,
		1, 1,
		0, 1,
		0, 0,
		1, 0,
		0, 1
	};
	SimpleModel::colors = nullptr;
	SimpleModel::init(program, GL_STATIC_DRAW);
	if (tex_fname)
		SimpleModel::initTexture(program, tex_fname);
}


Square::~Square()
{
}

void Square::draw()
{
	SimpleModel::draw(GL_TRIANGLES);
}
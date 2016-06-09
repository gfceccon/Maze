#include "square.h"



Square::Square(Program* program, const char* tex_fname)
{
	Model::nvertices = 6;
	//Model::nindices = 2;
	Model::vertices = new GLfloat[nvertices * 3]
	{
		 1.0f, -1.0f, 0.0f,  // Bottom Right
		 1.0f,  1.0f, 0.0f,  // Top Right
		-1.0f,  1.0f, 0.0f,  // Top Left 
		-1.0f, -1.0f, 0.0f,  // Bottom Left
		 1.0f, -1.0f, 0.0f,  // Bottom Right
		-1.0f,  1.0f, 0.0f   // Top Left 
	};
	Model::indices = nullptr;
	//Model::indices = new GLuint[nindices * 3]
	//{
	//	0, 1, 3,  // First Triangle
	//	1, 2, 3   // Second Triangle
	//};
	Model::uvs = new GLfloat[nvertices * 2]
	{
		1, 0,
		1, 1,
		0, 1,
		0, 0,
		1, 0,
		0, 1
	};
	Model::normals = nullptr;
	Model::colors = nullptr;
	Model::materials = nullptr;
	Model::init(program, GL_STATIC_DRAW);
	if (tex_fname)
		Model::initTexture(program, tex_fname);
}


Square::~Square()
{
}

void Square::draw()
{
	Model::draw(GL_TRIANGLES);
}

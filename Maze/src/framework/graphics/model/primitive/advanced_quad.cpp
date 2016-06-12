#include "advanced_quad.h"



AdvancedQuad::AdvancedQuad(Program* program) : Model()
{
	Model::nvertices = 6;
	Model::vertices = new GLfloat[nvertices * 3]
	{
		1.0f, -1.0f, 0.0f,		// Bottom Right
		1.0f,  1.0f, 0.0f,		// Top Right
		-1.0f,  1.0f, 0.0f,		// Top Left

		-1.0f, -1.0f, 0.0f,		// Bottom Left
		1.0f, -1.0f, 0.0f,		// Bottom Right
		-1.0f,  1.0f, 0.0f		// Top Left
	};
	Model::uvs = new GLfloat[nvertices * 2]
	{
		1, 0,
		1, 1,
		0, 1,
		0, 0,
		1, 0,
		0, 1
	};
	Model::normals = new GLfloat[nvertices * 3]
	{
		0,0,1,		// Bottom Right
		0,0,1,		// Top Right
		0,0,1,		// Top Left

		0,0,1,		// Bottom Left
		0,0,1,		// Bottom Right
		0,0,1		// Top Left
	};
	Model::init(program, GL_STATIC_DRAW);
}


AdvancedQuad::~AdvancedQuad()
{
}

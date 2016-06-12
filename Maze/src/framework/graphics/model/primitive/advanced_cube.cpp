#include "advanced_cube.h"



AdvancedCube::AdvancedCube(Program* program) : Model()
{
	Model::nvertices = 36;
	Model::vertices = new GLfloat[nvertices * 3]{
		0.0f, 0.0f, 0.0f,// Front Face
		1.0f, 0.0f, 0.0f,// Front Face
		1.0f, 1.0f, 0.0f,// Front Face
		1.0f, 1.0f, 0.0f,// Front Face
		0.0f, 1.0f, 0.0f,// Front Face
		0.0f, 0.0f, 0.0f,// Front Face

		0.0f, 0.0f, 1.0f,// Back Face
		1.0f, 0.0f, 1.0f,// Back Face
		1.0f, 1.0f, 1.0f,// Back Face
		1.0f, 1.0f, 1.0f,// Back Face
		0.0f, 1.0f, 1.0f,// Back Face
		0.0f, 0.0f, 1.0f,// Back Face

		0.0f, 1.0f, 1.0f,// Left Face
		0.0f, 1.0f, 0.0f,// Left Face
		0.0f, 0.0f, 0.0f,// Left Face
		0.0f, 0.0f, 0.0f,// Left Face
		0.0f, 0.0f, 1.0f,// Left Face
		0.0f, 1.0f, 1.0f,// Left Face

		1.0f, 1.0f, 1.0f,// Right Face
		1.0f, 1.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 1.0f,// Right Face
		1.0f, 1.0f, 1.0f,// Right Face

		0.0f, 0.0f, 0.0f,// Bottom Face
		1.0f, 0.0f, 0.0f,// Bottom Face
		1.0f, 0.0f, 1.0f,// Bottom Face
		1.0f, 0.0f, 1.0f,// Bottom Face
		0.0f, 0.0f, 1.0f,// Bottom Face
		0.0f, 0.0f, 0.0f,// Bottom Face

		0.0f, 1.0f, 0.0f,// Top Face
		1.0f, 1.0f, 0.0f,// Top Face
		1.0f, 1.0f, 1.0f,// Top Face
		1.0f, 1.0f, 1.0f,// Top Face
		0.0f, 1.0f, 1.0f,// Top Face
		0.0f, 1.0f, 0.0f // Top Face
	};
	Model::uvs = new GLfloat[nvertices * 2]{
		0.0f, 0.0f,// Front Face
		1.0f, 0.0f,// Front Face
		1.0f, 1.0f,// Front Face
		1.0f, 1.0f,// Front Face
		0.0f, 1.0f,// Front Face
		0.0f, 0.0f,// Front Face

		0.0f, 0.0f,// Back Face
		1.0f, 0.0f,// Back Face
		1.0f, 1.0f,// Back Face
		1.0f, 1.0f,// Back Face
		0.0f, 1.0f,// Back Face
		0.0f, 0.0f,// Back Face

		0.0f, 1.0f,// Left Face
		1.0f, 1.0f,// Left Face
		1.0f, 0.0f,// Left Face
		1.0f, 0.0f,// Left Face
		0.0f, 0.0f,// Left Face
		0.0f, 1.0f,// Left Face

		0.0f, 1.0f,// Right Face
		1.0f, 1.0f,// Right Face
		1.0f, 0.0f,// Right Face
		1.0f, 0.0f,// Right Face
		0.0f, 0.0f,// Right Face
		0.0f, 1.0f,// Right Face

		0.0f, 1.0f,// Bottom Face
		1.0f, 1.0f,// Bottom Face
		1.0f, 0.0f,// Bottom Face
		1.0f, 0.0f,// Bottom Face
		0.0f, 0.0f,// Bottom Face
		0.0f, 1.0f,// Bottom Face

		0.0f, 1.0f,// Top Face
		1.0f, 1.0f,// Top Face
		1.0f, 0.0f,// Top Face
		1.0f, 0.0f,// Top Face
		0.0f, 0.0f,// Top Face
		0.0f, 1.0f // Top Face
	};
	Model::normals = new GLfloat[nvertices * 3]{
		0.0f, 0.0f, -1.0f,// Front Face
		0.0f, 0.0f, -1.0f,// Front Face
		0.0f, 0.0f, -1.0f,// Front Face
		0.0f, 0.0f, -1.0f,// Front Face
		0.0f, 0.0f, -1.0f,// Front Face
		0.0f, 0.0f, -1.0f,// Front Face

		0.0f, 0.0f, 1.0f,// Back Face
		0.0f, 0.0f, 1.0f,// Back Face
		0.0f, 0.0f, 1.0f,// Back Face
		0.0f, 0.0f, 1.0f,// Back Face
		0.0f, 0.0f, 1.0f,// Back Face
		0.0f, 0.0f, 1.0f,// Back Face

		-1.0f, 0.0f, 0.0f,// Left Face
		-1.0f, 0.0f, 0.0f,// Left Face
		-1.0f, 0.0f, 0.0f,// Left Face
		-1.0f, 0.0f, 0.0f,// Left Face
		-1.0f, 0.0f, 0.0f,// Left Face
		-1.0f, 0.0f, 0.0f,// Left Face

		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face
		1.0f, 0.0f, 0.0f,// Right Face

		0.0f, -1.0f, 0.0f,// Bottom Face
		0.0f, -1.0f, 0.0f,// Bottom Face
		0.0f, -1.0f, 0.0f,// Bottom Face
		0.0f, -1.0f, 0.0f,// Bottom Face
		0.0f, -1.0f, 0.0f,// Bottom Face
		0.0f, -1.0f, 0.0f,// Bottom Face

		0.0f, 1.0f, 0.0f,// Top Face
		0.0f, 1.0f, 0.0f,// Top Face
		0.0f, 1.0f, 0.0f,// Top Face
		0.0f, 1.0f, 0.0f,// Top Face
		0.0f, 1.0f, 0.0f,// Top Face
		0.0f, 1.0f, 0.0f // Top Face
	};
	Model::init(program, GL_STATIC_DRAW);
}


AdvancedCube::~AdvancedCube()
{
}

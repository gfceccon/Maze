#include "simple_model.h"

#include <util/log.h>

SimpleModel::SimpleModel()
{
}


SimpleModel::~SimpleModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &nbo);
}

void SimpleModel::Init()
{
	if (!vertices)
		return;
	GLenum err;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	if(indices != nullptr)
		glGenBuffers(1, &ebo);
	if(normals != nullptr)
		glGenBuffers(1, &nbo);

	if ((err = glGetError()) != GL_NO_ERROR)
	{
		Log::Error(glewGetErrorString(err));
	}
}

void SimpleModel::Bind(GLenum drawing)
{
	if (!vertices)
		return;
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, nvertices * sizeof(GLfloat), vertices, drawing);

	if (indices)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nindices * sizeof(GLuint), indices, drawing);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void SimpleModel::Draw(GLenum mode)
{
	if (!vertices)
		return;
	glBindVertexArray(vao);

	glDrawElements(mode, nindices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
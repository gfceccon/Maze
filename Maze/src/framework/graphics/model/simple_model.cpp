#include "simple_model.h"

#include <util/log.h>

SimpleModel::SimpleModel()
{
}


SimpleModel::~SimpleModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	if(indices)
		glDeleteBuffers(1, &ebo);
	if(normals)
		glDeleteBuffers(1, &nbo);
}

void SimpleModel::init()
{
	if (!vertices)
		return;
	GLenum err;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	if(indices)
		glGenBuffers(1, &ebo);
	if(normals)
		glGenBuffers(1, &nbo);

	if ((err = glGetError()) != GL_NO_ERROR)
	{
		Log::error(glewGetErrorString(err));
	}
}

void SimpleModel::bind(GLenum drawing)
{
	if (!vertices)
		return;
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (indices)
	{
		glBufferData(GL_ARRAY_BUFFER, nvertices * sizeof(GLfloat), vertices, drawing);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nindices * sizeof(GLuint), indices, drawing);
	}
	else
		glBufferData(GL_ARRAY_BUFFER, 3 * nvertices * sizeof(GLfloat), vertices, drawing);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void SimpleModel::draw(GLenum mode)
{
	if (!vertices)
		return;
	glBindVertexArray(vao);

	if (indices)
		glDrawElements(mode, nindices, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, nvertices);

	glBindVertexArray(0);
}
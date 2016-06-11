#include "model.h"

#include <string>
#include <iostream>

Model::Model()
{
	vertices = nullptr;
	indices = nullptr;
	uvs = nullptr;
	normals = nullptr;
	tangents = nullptr;
	biTangents = nullptr;
	nvertices = 0;
	nindices = 0;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	if (vertex_buffer)
		delete vertex_buffer;

	if (indices)
	{
		glDeleteBuffers(1, &ebo);
		delete indices;
	}
}

GLsizei Model::initVertexBuffer()
{
	GLsizei stride = 3;

	if (uvs)
		stride += 2;

	if (normals)
		stride += 3;

	if (tangents)
		stride += 3;

	if (biTangents)
		stride += 3;

	vertex_buffer = new GLfloat[stride * nvertices];

	for (GLsizei i = 0; i < nvertices; i++)
	{
		int j = 0;
		vertex_buffer[i * stride + j++] = vertices[i * 3];
		vertex_buffer[i * stride + j++] = vertices[i * 3 + 1];
		vertex_buffer[i * stride + j++] = vertices[i * 3 + 2];


		if (uvs)
		{
			vertex_buffer[i * stride + j++] = uvs[i * 2];
			vertex_buffer[i * stride + j++] = uvs[i * 2 + 1];
		}

		if (normals)
		{
			vertex_buffer[i * stride + j++] = normals[i * 3];
			vertex_buffer[i * stride + j++] = normals[i * 3 + 1];
			vertex_buffer[i * stride + j++] = normals[i * 3 + 2];
		}

		if (tangents)
		{
			vertex_buffer[i * stride + j++] = tangents[i * 3];
			vertex_buffer[i * stride + j++] = tangents[i * 3 + 1];
			vertex_buffer[i * stride + j++] = tangents[i * 3 + 2];
		}

		if (biTangents)
		{
			vertex_buffer[i * stride + j++] = biTangents[i * 3];
			vertex_buffer[i * stride + j++] = biTangents[i * 3 + 1];
			vertex_buffer[i * stride + j++] = biTangents[i * 3 + 2];
		}
	}

	return stride;
}

void Model::init(Program* program, GLenum drawing)
{
	if (!vertices)
		throw std::runtime_error("Model loading fail, missing vertices!");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	if (indices) {
		glGenBuffers(1, &ebo);
	}

	GLsizei stride = initVertexBuffer();

	glBindVertexArray(vao);

	if (indices) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * nindices * sizeof(GLuint), indices, drawing);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)stride * nvertices * sizeof(GLfloat), vertex_buffer, drawing);

	GLint offset = 0;

	addVertexAttribute(program, "position", vertices, 3, stride, offset, sizeof(GLfloat));

	if (uvs)
		addVertexAttribute(program, "uv", uvs, 2, stride, offset, sizeof(GLfloat));

	if (normals)
		addVertexAttribute(program, "normals", uvs, 3, stride, offset, sizeof(GLfloat));

	if (tangents)
		addVertexAttribute(program, "tangents", tangents, 3, stride, offset, sizeof(GLfloat));

	if (biTangents)
		addVertexAttribute(program, "biTangents", biTangents, 3, stride, offset, sizeof(GLfloat));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::addVertexAttribute(Program* program, const char * attribute, void* buffer, GLint size, GLsizei & stride, GLint & offset, GLsizei typeSize)
{
	GLint index = program->getAttr(attribute);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * typeSize));
	glEnableVertexAttribArray(index);
	offset += size;

	delete buffer;
}

void Model::bind(Program* program)
{
	glBindVertexArray(vao);
}

void Model::draw(GLenum mode)
{
	if (indices) {
		glDrawElements(mode, nindices, GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(mode, 0, nvertices);
	}
}

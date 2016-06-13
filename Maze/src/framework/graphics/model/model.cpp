#include "model.h"

#include <string>
#include <iostream>

Model::Model() :
vertices(nullptr), indices(nullptr), uvs(nullptr), normals(nullptr), tangents(nullptr), bitangents(nullptr), nvertices(0), nindices(0)
{
	loadIdentity();
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

void Model::loadIdentity()
{
	model = glm::mat4();
}

void Model::scale(float x, float y, float z)
{
	model = glm::scale(model, glm::vec3(x, y, z));
}

void Model::rotate(float angle, int x, int y, int z)
{
	model = glm::rotate(model, glm::radians(angle), glm::vec3(x, y, z));
}

void Model::translate(float x, float y, float z)
{
	model = glm::translate(model, glm::vec3(x, y, z));
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

	if (bitangents)
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

		if (bitangents)
		{
			vertex_buffer[i * stride + j++] = bitangents[i * 3];
			vertex_buffer[i * stride + j++] = bitangents[i * 3 + 1];
			vertex_buffer[i * stride + j++] = bitangents[i * 3 + 2];
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

	addVertexAttribute(program, POSITION_ATTRIBUTE, vertices, 3, stride, offset);

	if (uvs)
		addVertexAttribute(program, UV_ATTRIBUTE, uvs, 2, stride, offset);

	if (normals)
		addVertexAttribute(program, NORMAL_ATTRIBUTE, normals, 3, stride, offset);

	if (tangents)
		addVertexAttribute(program, TANGENT_ATTRIBUTE, tangents, 3, stride, offset);

	if (bitangents)
		addVertexAttribute(program, BITANGENT_ATTRIBUTE, bitangents, 3, stride, offset);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::addVertexAttribute(Program* program, const char * attribute, void* buffer, GLint size, GLsizei stride, GLint & offset)
{
	GLint index = program->getAttr(attribute);
	if (index != -1)
	{
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		offset += size;
	}
	delete buffer;
}

void Model::bind(Program* program)
{
	glBindVertexArray(vao);
	program->setMat4(model, MODEL_MATRIX_NAME);
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

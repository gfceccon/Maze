#include "simple_model.h"

#include <string>
#include <iostream>
#include "../../../util/log.h"
#include "../../../../soil/src/SOIL.h"

SimpleModel::SimpleModel()
{
}


SimpleModel::~SimpleModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	if (vertex_buffer) {
		delete vertex_buffer;
	}

	if (vertices) {
		delete vertices;
	}

	if (indices) {
		glDeleteBuffers(1, &ebo);
		delete indices;
	}

	if (uvs) {
		//glDeleteBuffers(1, &uvbo);
		delete uvs;
	}

	if (colors) {
		//glDeleteBuffers(1, &nbo);
		delete colors;
	}

	if(hasTexture)
		glDeleteTextures(1, &texture);
	if(hasNormal)
		glDeleteTextures(1, &normal);
}

void SimpleModel::initImage(GLuint location, Program* program, const char* file_name)
{
	glBindTexture(GL_TEXTURE_2D, location);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(file_name, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SimpleModel::initTexture(Program* program, const char* file_name)
{
	glGenTextures(1, &texture);
	hasTexture = true;
	initImage(texture, program, file_name);
}

void SimpleModel::initNormal(Program* program, const char* file_name)
{
	glGenTextures(1, &normal);
	hasNormal = true;
	initImage(normal, program, file_name);
}

void SimpleModel::init(Program* program, GLenum drawing)
{
	if (!vertices)
		throw std::runtime_error("Model loading fail, missing vertices!");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	if (indices) {
		glGenBuffers(1, &ebo);
	}

	if (uvs) {
		//glGenBuffers(1, &uvbo);
	}

	if (colors) {
		//glGenBuffers(1, &nbo);
	}
	
	GLsizei stride = 3;

	if (uvs) {
		stride += 2;
	}

	if (colors) {
		stride += 3;
	}

	vertex_buffer = new GLfloat[stride * nvertices];

	for (GLsizei i = 0; i < nvertices; i++)
	{
		vertex_buffer[i * stride] = vertices[i * 3];
		vertex_buffer[i * stride + 1] = vertices[i * 3 + 1];
		vertex_buffer[i * stride + 2] = vertices[i * 3 + 2];


		if (uvs)
		{
			vertex_buffer[i * stride + 3] = uvs[i * 2];
			vertex_buffer[i * stride + 4] = uvs[i * 2 + 1];
		}

		if (colors)
		{
			vertex_buffer[i * stride + 5] = colors[i * 3];
			vertex_buffer[i * stride + 6] = colors[i * 3 + 1];
			vertex_buffer[i * stride + 7] = colors[i * 3 + 2];
		}
	}

	glBindVertexArray(vao);

	if (indices) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * nindices * sizeof(GLuint), indices, drawing);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)stride * nvertices * sizeof(GLfloat), vertex_buffer, drawing);

	GLint index = program->getAttr("position");
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(index);

	delete vertices;
	vertices = nullptr;

	if (uvs)
	{
		GLint index = program->getAttr("texCoord");
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(3 *sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		delete uvs;
		uvs = nullptr;
	}

	if (colors)
	{
		GLint index = program->getAttr("color");
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(5 *sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		delete colors;
		colors = nullptr;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SimpleModel::bind(Program* program)
{
	glBindVertexArray(vao);
	if (hasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		program->setInt(0, "texture2D");
	}
	if (hasNormal)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normal);
		program->setInt(1, "normal2D");
	}
}

void SimpleModel::draw(GLenum mode)
{
	if (indices) {
		glDrawElements(mode, nindices, GL_UNSIGNED_INT, 0);
	} else {
		glDrawArrays(mode, 0, nvertices);
	}
}

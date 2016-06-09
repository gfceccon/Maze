#include "model.h"

#include <string>
#include <iostream>

Model::Model()
{
}

Model::~Model()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	if (vertex_buffer)
		delete vertex_buffer;

	if (vertices)
		delete vertices;

	if (indices)
	{
		glDeleteBuffers(1, &ebo);
		delete indices;
	}

	if (uvs)
		delete uvs;

	if (normals)
		delete normals;

	if (colors)
		delete colors;

	if (materials)
		delete materials;

	if (hasTexture)
		glDeleteTextures(1, &texture);
	if (hasNormal)
		glDeleteTextures(1, &normal);
}

void Model::initImage(GLuint location, Program* program, const char* file_name)
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

void Model::initTexture(Program* program, const char* file_name)
{
	glGenTextures(1, &texture);
	hasTexture = true;
	initImage(texture, program, file_name);
}

void Model::initNormalMap(Program* program, const char* file_name)
{
	glGenTextures(1, &normal);
	hasNormal = true;
	initImage(normal, program, file_name);
}

void Model::initDepthMap(Program* program, const char* file_name)
{
	glGenTextures(1, &depth);
	hasDepth = true;
	initImage(depth, program, file_name);
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

	GLsizei stride = 3;

	if (uvs)
		stride += 2;

	if (colors)
		stride += 3;

	if (materials)
		stride += 1;

	vertex_buffer = new GLfloat[stride * nvertices];

	for (GLsizei i = 0; i < nvertices; i++)
	{
		int j = 0;
		vertex_buffer[i * stride] = vertices[i * 3];
		j++;
		vertex_buffer[i * stride + j] = vertices[i * 3 + 1];
		j++;
		vertex_buffer[i * stride + j] = vertices[i * 3 + 2];
		j++;


		if (uvs)
		{
			vertex_buffer[i * stride + j] = uvs[i * 2];
			j++;
			vertex_buffer[i * stride + j] = uvs[i * 2 + 1];
			j++;
		}

		if (normals)
		{
			vertex_buffer[i * stride + j] = normals[i * 3];
			j++;
			vertex_buffer[i * stride + j] = normals[i * 3 + 1];
			j++;
			vertex_buffer[i * stride + j] = normals[i * 3 + 2];
			j++;
		}

		if (colors)
		{
			vertex_buffer[i * stride + j] = colors[i * 3];
			j++;
			vertex_buffer[i * stride + j] = colors[i * 3 + 1];
			j++;
			vertex_buffer[i * stride + j] = colors[i * 3 + 2];
			j++;
		}

		if (materials)
		{
			vertex_buffer[i * stride + j] = materials[i];
			j++;
		}
	}

	glBindVertexArray(vao);

	if (indices) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * nindices * sizeof(GLuint), indices, drawing);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)stride * nvertices * sizeof(GLfloat), vertex_buffer, drawing);

	int offset = 0;

	GLint index = program->getAttr("position");
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)offset);
	glEnableVertexAttribArray(index);
	offset += 3;

	delete vertices;
	vertices = nullptr;

	if (uvs)
	{
		GLint index = program->getAttr("uv");
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		offset += 2;
		delete uvs;
		uvs = nullptr;
	}

	if (normals)
	{
		GLint index = program->getAttr("normal");
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		offset += 3;
		delete colors;
		colors = nullptr;
	}

	if (colors)
	{
		GLint index = program->getAttr("color");
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		offset += 3;
		delete colors;
		colors = nullptr;
	}

	if (materials)
	{
		GLint index = program->getAttr("materialIndex");
		glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(index);
		offset += 1;
		delete colors;
		colors = nullptr;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::bind(Program* program, Material* material)
{
	glBindVertexArray(vao);
	if (hasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		if (material != nullptr)
			program->setInt(0, material->getAttribute("diffuse2D"));
		else
			program->setInt(0, "texture2D");
	}
	if (hasNormal)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normal);
		if (material != nullptr)
			program->setInt(1, material->getAttribute("normal2D"));
		else
			program->setInt(1, "normal2D");
	}
	if (hasDepth)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, depth);
		if (material != nullptr)
			program->setInt(2, material->getAttribute("depth2D"));
		else
			program->setInt(2, "depth2D");
	}
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

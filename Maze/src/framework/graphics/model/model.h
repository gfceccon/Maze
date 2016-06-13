#pragma once

#include <GL/glew.h>
#include "material.h"
#include "../shader/program.h"
#include "../../../util/log.h"
#include "../../../util/glm/mat4x4.hpp"
#include "../../../util/glm/gtc/matrix_transform.hpp"

#define POSITION_ATTRIBUTE "position"
#define UV_ATTRIBUTE "uv"
#define NORMAL_ATTRIBUTE "normal"
#define TANGENT_ATTRIBUTE "tangent"
#define BITANGENT_ATTRIBUTE "bitangent"

#define MODEL_MATRIX_NAME "model"

class Model
{
	GLuint vao, vbo, ebo;
	GLfloat *vertex_buffer;

	GLsizei initVertexBuffer();
	glm::mat4 model;
protected:
	GLfloat *vertices, *uvs, *normals, *tangents, *bitangents;
	GLuint *indices;
	GLsizei nvertices, nindices;
	void init(Program* program, GLenum drawing);
	void addVertexAttribute(Program* program, const char* attribute, void* vertex, GLint size, GLsizei stride, GLint& offset);
public:
	Model();
	virtual ~Model();

	void loadIdentity();
	void scale(float x, float y, float z);
	void rotate(float angle, int x, int y, int z);
	void translate(float x, float y, float z);

	void bind(Program* program);
	void draw(GLenum mode);

	virtual void draw() { draw(GL_TRIANGLES); };
};


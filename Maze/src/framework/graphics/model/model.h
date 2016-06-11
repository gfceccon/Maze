#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/log.h"
#include "material.h"

class Model
{
	GLuint vao, vbo, ebo;
	GLfloat *vertex_buffer;

	GLsizei initVertexBuffer();
protected:
	GLfloat *vertices, *uvs, *normals, *tangents, *biTangents;
	GLuint *indices;
	GLsizei nvertices, nindices;
	void init(Program* program, GLenum drawing);
	void addVertexAttribute(Program* program, const char* attribute, void* vertex, GLint size, GLsizei& stride, GLint& offset, GLsizei typeSize);
public:
	Model();
	virtual ~Model();
	void bind(Program* program);
	void draw(GLenum mode);
	virtual void draw() { draw(GL_TRIANGLES); };
};


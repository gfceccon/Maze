#pragma once

#include <GL/glew.h>
#include "../shader/program.h"

class SimpleModel
{
	GLuint vao, vbo, ebo, texture, normal;
	GLfloat *vertex_buffer;
	bool hasTexture = false, hasNormal = false;
protected:
	GLfloat *vertices, *uvs, *colors;
	GLuint *indices;
	GLsizei nvertices, nindices;
	void initImage(GLuint location, Program* program, const char* file_name);
	void initTexture(Program* program, const char* file_name);
	void initNormal(Program* program, const char* file_name);
	void init(Program* program, GLenum drawing);
public:
	SimpleModel();
	virtual ~SimpleModel();
	void bind(Program* program);
	void draw(GLenum mode);
	virtual void draw() { draw(GL_STATIC_DRAW); };
};


#pragma once

#include <GL/glew.h>

class SimpleModel
{
protected:
	GLuint vao, vbo, ebo, nbo;
	GLfloat *vertices, *normals;
	GLuint *indices;
	GLsizei nvertices, nindices, nnormals;
	void init();
public:
	SimpleModel();
	~SimpleModel();
	void bind(GLenum drawing);
	void draw(GLenum mode);
	virtual void draw() { bind(GL_TRIANGLES); };
	virtual void bind() { draw(GL_STATIC_DRAW); };
};


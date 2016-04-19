#pragma once

#include <GL/glew.h>

class SimpleModel
{
protected:
	GLuint vao, vbo, ebo, nbo;
	GLfloat *vertices, *normals;
	GLuint *indices;
	GLsizei nvertices, nindices, nnormals;
	void Init();
public:
	SimpleModel();
	~SimpleModel();
	void Bind(GLenum drawing);
	void Draw(GLenum mode);
	virtual void Draw() { Bind(GL_TRIANGLES); };
	virtual void Bind() { Draw(GL_STATIC_DRAW); };
};


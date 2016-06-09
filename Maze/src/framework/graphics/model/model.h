#pragma once

#include <GL/glew.h>
#include "../shader/program.h"
#include "../../../util/log.h"
#include "../../../../soil/src/SOIL.h"
#include "material.h"

class Model
{
	GLuint vao, vbo, ebo, texture, normal, depth;
	GLfloat *vertex_buffer;
	bool hasTexture = false, hasNormal = false, hasDepth = false;
protected:
	GLfloat *vertices, *uvs, *normals, *colors;
	GLuint *indices;
	GLint *materials;
	GLsizei nvertices, nindices;
	void initImage(GLuint location, Program* program, const char* file_name);
	void initTexture(Program* program, const char* file_name);
	void initNormalMap(Program* program, const char* file_name);
	void initDepthMap(Program* program, const char* file_name);
	void init(Program* program, GLenum drawing);
public:
	Model();
	virtual ~Model();
	void bind(Program* program, Material* material = nullptr);
	void draw(GLenum mode);
	virtual void draw() { draw(GL_TRIANGLES); };
};


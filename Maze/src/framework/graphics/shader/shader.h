#pragma once

#include <GL/glew.h>

class Shader
{
	const char* path = "resources/";
	GLuint shader;
public:
	Shader(const char* fname, GLenum type, GLuint program);
	~Shader();
};
#pragma once

#include <GL/glew.h>

class Shader
{
	private:
		GLuint shader;
	public:
		Shader(const char* fname, GLenum type, GLuint program);
		~Shader();
};

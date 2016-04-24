#pragma once

#include <GL/glew.h>

class Shader
{
	private:
		GLuint shader;
		const char* path = "resources/";
	public:
		Shader(const char* fname, GLenum type, GLuint program);
		~Shader();
};

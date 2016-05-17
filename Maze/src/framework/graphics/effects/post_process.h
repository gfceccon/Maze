#pragma once

#include <GL/glew.h>
#include "../model/primitive/square.h"
#include "../shader/program.h"

class PostProcess
{
	const glm::vec4 clear_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	GLuint fbo, rbo, textureID;
	Square* quad;
protected:
	Program* program;
	virtual void beginDraw();
	virtual void endDraw();
public:
	PostProcess(int width, int height, Program* program, GLboolean depth = GL_FALSE, GLboolean stencil = GL_FALSE);
	virtual ~PostProcess();
	void bind();
	virtual void draw();
};


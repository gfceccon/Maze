#include "timed_effectt.h"



TimedEffect::TimedEffect(const char* uniform, int width, int height, Program* program) :
	PostProcess(width, height, program, GL_FALSE, GL_FALSE)
{
	time = 0.0f;
	this->uniform = uniform;
}

void TimedEffect::bind()
{
	PostProcess::bind();
}

void TimedEffect::beginDraw()
{
	PostProcess::beginDraw();
	program->setFloat(time, uniform);
}

void TimedEffect::draw()
{
}

void TimedEffect::draw(float delta)
{
	time += delta;
	draw();
}
#include "chrom_aberr.h"

ChromAberr::ChromAberr(int width, int height, Program* program) :
	TimedEffect("time", width, height, program)
{
	this->width = width;
	this->height = height;
}

void ChromAberr::init(const char* red_uniform, glm::vec2 red_offset, const char* green_uniform, glm::vec2 green_offset, const char* blue_uniform, glm::vec2 blue_offset)
{
	this->red_uniform = red_uniform;
	this->green_uniform = green_uniform;
	this->blue_uniform = blue_uniform;

	this->red_offset = red_offset;
	this->green_offset = green_offset;
	this->blue_offset = blue_offset;
}

void ChromAberr::draw(float delta)
{
	TimedEffect::draw(delta);
	TimedEffect::beginDraw();
	program->setVec2(red_offset, red_uniform);
	program->setVec2(green_offset, green_uniform);
	program->setVec2(blue_offset, blue_uniform);
	program->setVec2(glm::vec2((float)width, (float)height), "resolution");
	TimedEffect::endDraw();
}

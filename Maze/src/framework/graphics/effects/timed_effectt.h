#pragma once

#include "post_process.h"

class TimedEffect : protected PostProcess
{
	const char* uniform;
	void draw() override;
protected:
	float time;
	void beginDraw() override;
public:
	TimedEffect(const char* uniform, int width, int height, Program* program);
	void bind();
	virtual void draw(float delta);
};


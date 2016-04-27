#pragma once

#include "post_process.h"

class TimedEffect : protected PostProcess
{
	char* uniform;
	void draw() override;
protected:
	float time;
	void beginDraw() override;
public:
	TimedEffect(char* uniform, int width, int height, Program* program);
	~TimedEffect();
	void bind();
	virtual void draw(float delta);
};


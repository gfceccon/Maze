#pragma once

enum EventType
{
	KEY,
	MOUSE,
	SCROLL
};

class Event
{
public:
	EventType type;
	int key, scancode, action, mods;
	float x, y;

	Event(int key, int scancode, int action, int mods);
	Event(float xpos, float ypos, bool isScroll = false);
	~Event();
};


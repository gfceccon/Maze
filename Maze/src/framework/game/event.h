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
	double x, y;

	Event(int key, int scancode, int action, int mods);
	Event(double xpos, double ypos, bool isScroll = false);
	~Event();
};


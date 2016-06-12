#include "event.h"



Event::Event(int key, int scancode, int action, int mods) :
	type(EventType::KEY), key(key), scancode(scancode), action(action), mods(mods)
{
}

Event::Event(double xpos, double ypos, bool isScroll) : x(xpos), y(ypos)
{
	if (isScroll)
		type = EventType::SCROLL;
	else
		type = EventType::MOUSE;
}


Event::~Event()
{
}

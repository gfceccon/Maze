#include "event.h"



Event::Event(int key, int scancode, int action, int mods) : 
	key(key), scancode(scancode), action(action), mods(mods), type(EventType::KEY)
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

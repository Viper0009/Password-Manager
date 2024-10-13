#pragma once
#include "../Header.h"
class State
{
public:
	virtual void refresh();
	virtual void draw(RenderWindow& window);
	virtual void update(RenderWindow& window, double elTime);
	virtual void check(Event& event);
};


#pragma once
#include "UiDesign.h"
#include "Drawer.h"
class Checkable {
public:
	virtual void check(Event& event);
};

class Checker
{
public:
	static void check(Drawable& checkable, Event& event);
	static void check(Checkable& checkable, Event& event);

};


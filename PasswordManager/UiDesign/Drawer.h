#pragma once
#include "UiDesign.h"
class SelfDrawable
{
private:
public:
	virtual void draw(RenderWindow& window) const = 0;
};

class Drawer {
private:
public:
	static void draw(const Drawable& drawable, RenderWindow& window);
	static void draw(const SelfDrawable& drawable, RenderWindow& window);
};

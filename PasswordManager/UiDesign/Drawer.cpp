#include "Drawer.h"

void Drawer::draw(const Drawable& drawable, RenderWindow& window)
{
	window.draw(drawable);
}

void Drawer::draw(const SelfDrawable& drawable, RenderWindow& window)
{
	drawable.draw(window);
}

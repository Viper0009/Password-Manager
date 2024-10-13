#include "Checker.h"

void Checker::check(Drawable& checkable, Event& event)
{
}

void Checker::check(Checkable& checkable, Event& event)
{
	checkable.check(event);
}
void Checkable::check(Event& event)
{}

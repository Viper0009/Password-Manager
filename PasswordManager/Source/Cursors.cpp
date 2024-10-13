#include "Cursors.h"

void Cursors::init1()
{
	arrow.loadFromSystem(Cursor::Arrow);
	wait.loadFromSystem(Cursor::Wait);
	hand.loadFromSystem(Cursor::Hand);
	text.loadFromSystem(Cursor::Text);
	help.loadFromSystem(Cursor::Help);
}

Cursors::Cursors()
{
	init1();
}

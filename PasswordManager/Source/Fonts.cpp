#include "Fonts.h"

void Fonts::init1()
{
	basic.loadFromFile("regular.otf");
}

Fonts::Fonts() {
	init1();
}
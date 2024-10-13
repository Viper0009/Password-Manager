#pragma once
#include "Header.h"
#include "Factory.h"
#include "Resource.h"
#include "SFML/Main.hpp"
void prepare();
void destruct();
void mainCheck(Event& event, RenderWindow& window,bool& resized);
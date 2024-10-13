#pragma once
#include "SFML/System/String.hpp"
#include "Question.h"
class Blank
{
public:
	sf::String title, password;
	Question q;
	Question::Type qt;
	Blank(const sf::String& title, const sf::String& password, const Question& q, const Question::Type& qt);
};


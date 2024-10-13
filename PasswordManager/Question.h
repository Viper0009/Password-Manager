#pragma once
#include "vector"
#include "SFML/System/String.hpp"
typedef std::vector<sf::String> QuestionAnswersContainer;
class Question
{
public:
	enum Type {
		Test,
		Enter
	};
	QuestionAnswersContainer
		rightAnswers,
		wrongAnswers;
	sf::String question;
	Question(sf::String question, const QuestionAnswersContainer& rightAnswers, const QuestionAnswersContainer& wrongAnswers);
	bool isRight(const sf::String& answ);
	bool operator==(const Question& _right) const;
	bool operator!=(const Question& _right) const;
	static Question Null;
};


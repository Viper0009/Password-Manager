#include "Question.h"

Question::Question(sf::String question, const QuestionAnswersContainer& rightAnswers, const QuestionAnswersContainer& wrongAnswers) :
	question(question), rightAnswers(rightAnswers), wrongAnswers(wrongAnswers)
{
}

bool Question::isRight(const sf::String& answ)
{
    return find(rightAnswers.begin(), rightAnswers.end(), answ) != rightAnswers.end();
}

bool Question::operator==(const Question& _right) const
{
	return this->question == _right.question && this->rightAnswers == _right.rightAnswers && this->wrongAnswers == _right.wrongAnswers;
}
bool Question::operator!=(const Question& _right) const
{
	return !(*this == _right);
}
Question Question::Null = Question(L"NULL", {}, {});
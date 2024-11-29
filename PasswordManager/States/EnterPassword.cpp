#include "States.h"
States::EnterPassword::EnterPassword(States& states) : states(states),
title(states.r.fact.getTextBox(Vector2f(80vw, 20vh), L"Авторизация", Vector2f(10vw, 5vh))),
input(states.r.fact.getInputTextBox(Vector2f(70vw, 20vh), L"Введите пароль", Vector2f(15vw, 35vh))),
output(states.r.fact.getTextBox(Vector2f(70vw, 10vh), L"", Vector2f(15vw, 60vh))),
enterButton(states.r.fact.getButton(Vector2f(20vw, 15vh), L"Готово", Vector2f(15vw, 75vh))),
answerQuestionButton(states.r.fact.getButton(Vector2f(20vw, 15vh), L"Ответить на вопрос", Vector2f(40vw, 75vh))),
backButton(states.r.fact.getButton(Vector2f(20vw, 15vh), L"Назад", Vector2f(65vw, 75vh))),
timer(states.r.fact.getTextBox(Vector2f(30vw, 10vh), L"", Vector2f(35vw, 90vh - 3vh)))
{
	output.setTextFillColor(states.r.colors.outputText);
	enterButton.setEnable(false);
	//enterButton.getRect().setTextOffset(Vector2f(0, -0.5));
	//answerQuestionButton.getRect().setTextOffset(Vector2f(0, -0.1));
	input.getRect().setStringSizeLimit(states.characterInputLimit);
	timer.setFillColor(Color::Transparent);
}
void States::EnterPassword::refresh() {
	answerQuestionButton.setEnable(states.currentBlank->q != Question::Null);
}
void States::EnterPassword::check(Event& event)
{
	title.check(event);
	input.check(event);
	enterButton.setEnable(!input.getRect().getString().isEmpty());
	output.check(event);
	enterButton.check(event);
	answerQuestionButton.check(event);
	backButton.check(event);
	answerQuestionButton.setEnable(states.currentBlank->q != Question::Null);
	if (input.isClicked()) {
		output.setString(L"");
	}
	if (enterButton.isClicked()) {
		if (input.getRect().getString() == states.r.mainPassword) {
			states.authorized = true;
			states.currentState = &states.passwordBlank;
			states.currentState->refresh();
			input.getRect().setString(L"");
			enterButton.setEnable(false);
		}
		else
			output.setString(L"Неверный пароль. Попробуйте ещё раз");
	}
	if (answerQuestionButton.isClicked()) {
		states.currentState = &states.answerQuestion;
		states.currentState->refresh();
	}
	if (backButton.isClicked()) {
		states.currentState = &states.chooseBlank;
		states.currentState->refresh();
	}
}

void States::EnterPassword::draw(RenderWindow& window)
{
	answerQuestionButton.draw(window);
	title.draw(window);
	input.draw(window);
	output.draw(window);
	enterButton.draw(window);
	answerQuestionButton.draw(window);
	backButton.draw(window);
}
static String getTimerString(int seconds) {
	int mins = seconds / 60;
	if (mins > 0) {
		String minutes;
		if (seconds % 100 < 20 && seconds % 100 > 10)
			minutes = L"минут";
		else if (seconds % 10 == 1)
			minutes = L"минуту";
		else if (seconds % 10 > 1 && seconds % 10 < 5)
			minutes = L"минуты";
		else
			minutes = L"минут";
		return L"Повторите попытку через " + std::to_wstring(mins) + minutes;
	}
	else
		return L"Повторите попытку меньше, чем через минуту";
}
void States::EnterPassword::update(RenderWindow& window, double elTime)
{
	time_t atNow = time(0);
	if (atNow < states.r.timerList[states.currentBlankIndex]) {
		timer.setString(getTimerString(states.r.timerList[states.currentBlankIndex] - atNow));
		answerQuestionButton.setEnable(false);
		timer.draw(window);
	}
	answerQuestionButton.update(window);
	title.draw(window);
	input.update(window);
	output.draw(window);
	enterButton.update(window);
	answerQuestionButton.update(window);
	backButton.update(window);
}

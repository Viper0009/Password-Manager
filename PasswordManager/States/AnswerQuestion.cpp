#include "States.h"
static std::default_random_engine dre{ unsigned int(time(0) - 0xcabf) };
static const int waitSeconds = 1800;
States::AnswerQuestion::AnswerQuestion(States& states) :
	states(states), failed(false),
	input(states.r.fact.getInputTextBox(Vector2f(70vw, 15vh), L"Введите ответ", Vector2f(15vw, 45vh))),
	output(states.r.fact.getTextBox(Vector2f(70vw, 10vh), L"", Vector2f(15vw, 65vh))),
	enter(states.r.fact.getButton(Vector2f(65vw, 15vh), L"Готово", Vector2f(17.5vw, 80vh))),
	title(states.r.fact.getTextBox(Vector2f(60vw, 10vh), L"Ответьте на вопрос", Vector2f(20vw, 5vh))),
	question(states.r.fact.getTextBox(Vector2f(70vw, 20vh), L"...", Vector2f(15vw, 20vh))),
	back(states.r.fact.getButton(Vector2f(65vw, 15vh), L"Назад", Vector2f(17.5vw, 80vh))),
	back1(states.r.fact.getButton(Vector2f(70vw, 10vh), L"Назад", Vector2f(15vw, 85vh))),
	buttons{
	(states.r.fact.getButton(Vector2f(35vw, 10vh), L"", Vector2f(12.5vw, 45vh))),
	(states.r.fact.getButton(Vector2f(35vw, 10vh), L"", Vector2f(52.5vw, 45vh))),
	(states.r.fact.getButton(Vector2f(35vw, 10vh), L"", Vector2f(12.5vw, 57.5vh))),
	(states.r.fact.getButton(Vector2f(35vw, 10vh), L"", Vector2f(52.5vw, 57.5vh)))
	}
{
	question.setCharacterSize(40px);
	output.setTextFillColor(states.r.colors.outputText);
	input.getRect().setStringSizeLimit(states.characterInputLimit);
}

void States::AnswerQuestion::refresh()
{
	if (states.currentBlank) {
		question.setString(states.currentBlank->q.question);
		switch (states.currentBlank->qt) {
		case Question::Enter: {
			attempts = 3;
			input.getRect().setString(L"");
			output.setString(L"У вас есть " + std::to_wstring(attempts) + L" попытки");
			output.setPosition(Vector2f(15vw, 65vh));
		} break;
		case Question::Test: {
			states.r.timerList[states.currentBlankIndex] = time(0) + waitSeconds;
			failed = false;
			back1.setEnable(failed);
			output.setPosition(Vector2f(15vw, 70vh));
			output.setString(L"");
			for (auto& i : buttons)
				i.get().getRect().setString(L"");
			QuestionAnswersContainer qa(states.currentBlank->q.wrongAnswers);
			std::shuffle(qa.begin(), qa.end(), dre);
			sf::String rightAnswer = states.currentBlank->q.rightAnswers[rand() % states.currentBlank->q.rightAnswers.size()];
			vector<std::reference_wrapper<TButton>> tempButtons(buttons.begin(), std::min(buttons.begin() + 1 + qa.size(), buttons.end()));
			std::shuffle(tempButtons.begin(), tempButtons.end(), dre);
			{
				int i = 0;
				for (; i < buttons.size() - 1 && i < qa.size(); ++i)
					tempButtons[i].get().getRect().setString(qa[i]);
				tempButtons[i].get().getRect().setString(rightAnswer);
			}
		} break;
		}
	}
}

void States::AnswerQuestion::check(Event& event)
{
	switch (states.currentBlank->qt) {
	case Question::Enter: {
		input.check(event);
		output.check(event);
		if (attempts)
			enter.check(event);
		else
			back.check(event);
		if (back.isClicked())
			switchState(states.enterPassword);
		if (enter.isClicked()) {
			if (states.currentBlank->q.isRight(input.getRect().getString())) {
				switchState(states.passwordBlank);
			}
			else if (!input.getRect().getString().isEmpty()){
				attempts -= (bool)attempts;
				if (attempts % 10 > 1 && attempts % 10 < 5)
					output.setString(L"Неправильный ответ. У вас осталось " + std::to_wstring(attempts) + L" попытки");
				else if (attempts % 10 == 1)
					output.setString(L"Неправильный ответ. У вас осталась " + std::to_wstring(attempts) + L" попытка");
				else if (attempts == 0)
					output.setString(L"Неправильный ответ. Попытки закончились");
				else 
					output.setString(L"Неправильный ответ. У вас осталось " + std::to_wstring(attempts) + L" попыток");
				if (!attempts) {
					states.r.timerList[states.currentBlankIndex] = time(0) + 60;
				}
			}
		}
	} break;
	case Question::Test: {
		if(!failed)
		for (auto& i : buttons) {
			i.get().check(event);
			if (i.get().isClicked() && !i.get().getRect().getString().isEmpty()) {
				if (states.currentBlank->q.isRight(i.get().getRect().getString())) {
					states.r.timerList[states.currentBlankIndex] = 0;
					switchState(states.passwordBlank);
				}
				else {
					output.setString(L"Неправильный ответ, повторите попытку позже");
					failed = true;
					back1.setEnable(failed);
				}
			}
		}
		else {
			back1.check(event);
			if (back1.isClicked())
				switchState(states.enterPassword);
		}
	} break;
	}
}

void States::AnswerQuestion::draw(RenderWindow& window)
{
	switch (states.currentBlank->qt) {
	case Question::Enter: {
		title.draw(window);
		question.draw(window);
		input.draw(window);
		output.draw(window);
		enter.draw(window);
	} break;
	case Question::Test: {
		title.draw(window);
		question.draw(window);
		for (auto& i : buttons)
			i.get().draw(window);
		output.draw(window);
		back1.draw(window);
	} break;
	}
}

void States::AnswerQuestion::update(RenderWindow& window, double elTime)
{
	switch (states.currentBlank->qt) {
	case Question::Enter: {
		title.draw(window);
		question.draw(window);
		input.update(window);
		output.draw(window);
		if (attempts) {
			enter.update(window);
		}
		else
			back.update(window);
	} break;
	case Question::Test: {
		title.draw(window);
		question.draw(window);
		if (!failed)
			for (auto& i : buttons)
				i.get().update(window);
		else
			for (auto& i : buttons)
				i.get().draw(window);
		output.draw(window);
		back1.update(window);
	} break;
	}
}

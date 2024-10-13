#include "States.h"
States::Intro::Welcome::Welcome(States& states) : states(states),
title(states.r.fact.getTextBox(Vector2f(70vw, 20vh), L"Менеджер паролей", Vector2f(15vw, 5vh))),
welcome(states.r.fact.getTextBox(Vector2f(80vw, 15vh), L"Добро пожаловать", Vector2f(10vw, 30vh))),
next(states.r.fact.getButton(Vector2f(70vw, 15vh), L"Далее", Vector2f(15vw, 80vh)))
{
	title.setCharacterSize(70px);
}
void States::Intro::Welcome::check(Event& event)
{
	next.check(event);
	if (next.isClicked()) {
		states.currentState = &states.intro.about;
		states.intro.about.refresh();
	}
}
void States::Intro::Welcome::draw(RenderWindow& window)
{
	title.draw(window);
	welcome.draw(window);
	next.draw(window);
}
void States::Intro::Welcome::update(RenderWindow& window, double elTime)
{
	title.draw(window);
	welcome.draw(window);
	next.update(window);
}
States::Intro::About::About(States& states) : states(states),
title(states.r.fact.getTextBox(Vector2f(70vw, 15vh), L"О программе", Vector2f(15vw, 5vh))),
info(states.r.fact.getTextBox(Vector2f(80vw, 40vh), L"", Vector2f(10vw, 25vh))),
next(states.r.fact.getButton(Vector2f(70vw, 20vh), L"Далее", Vector2f(15vw, 75vh)))
{
	info.setAlign(Align::Left);
	info.setCharacterSize(25px);
	info.setTextOffset(Vector2f());
	info.setString(
		std::wstring(L"Менеджер паролей позволяет хранить различные пароли в одном месте, зная один единственный пароль. ") +
		L"Также, можно получить пароль ответив на личный вопрос, на который знает ответ только эта личность. " +
		L"Простой интерфейс делает пользование интуитивно понятным, а шифрование — хранение паролей безопасным."
	);
}
void States::Intro::About::check(Event& event)
{
	next.check(event);
	if (next.isClicked()) {
		states.currentState = &states.intro.createPassword;
		states.currentState->refresh();
	}
}
void States::Intro::About::draw(RenderWindow& window)
{
	title.draw(window);
	info.draw(window);
	next.draw(window);
}
void States::Intro::About::update(RenderWindow& window, double elTime)
{
	title.draw(window);
	info.draw(window);
	next.update(window);
}
States::Intro::CreatePassword::CreatePassword(States& states) : states(states),
title(states.r.fact.getTextBox(Vector2f(70vw, 15vh), L"Придумайте пароль", Vector2f(15vw, 5vh))),
writePassword(states.r.fact.getInputTextBox(Vector2f(80vw, 20vh), L"Введите пароль", Vector2f(10vw, 25vh))),
repeatPassword(states.r.fact.getInputTextBox(Vector2f(80vw, 20vh), L"Подтвердите пароль", Vector2f(10vw, 50vh))),
enter(states.r.fact.getButton(Vector2f(70vw, 20vh), L"Готово", Vector2f(15vw, 75vh)))
{
	writePassword.getRect().setStringSizeLimit(states.characterInputLimit);
	repeatPassword.getRect().setStringSizeLimit(states.characterInputLimit);
}
void States::Intro::CreatePassword::refresh()
{
	writePassword.getRect().setString(L"");
	repeatPassword.getRect().setString(L"");
	enter.setEnable(false);
}
void States::Intro::CreatePassword::check(Event& event) {
	writePassword.check(event);
	repeatPassword.check(event);
	if (event.type == Event::TextEntered)
		enter.setEnable(writePassword.getRect().getString() == repeatPassword.getRect().getString() &&
			!writePassword.getRect().getString().isEmpty());
	enter.check(event);
	if (enter.isClicked()) {
		states.r.mainPassword = writePassword.getRect().getString();
		states.currentState = &states.mainMenu;
	}
}
void States::Intro::CreatePassword::draw(RenderWindow& window) {
	title.draw(window);
	writePassword.draw(window);
	repeatPassword.draw(window);
	enter.draw(window);
}
void States::Intro::CreatePassword::update(RenderWindow& window, double elTime) {
	title.draw(window);
	writePassword.update(window);
	repeatPassword.update(window);
	enter.update(window);
}
States::Intro::Intro(States& states) : states(states),
	welcome(states),
	about(states),
	createPassword(states)
{
}

void States::Intro::refresh()
{
	states.currentState = &welcome;
	welcome.refresh();
}

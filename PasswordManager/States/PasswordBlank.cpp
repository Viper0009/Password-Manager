#include "States.h"
States::PasswordBlank::PasswordBlank(States& states) :
	states(states), showPassword(false),
	title(states.r.fact.getTextBox(Vector2f(70vw, 10vh), L"Бланк с паролем", Vector2f(15vw, 5vh))),
	bTitle(states.r.fact.getTextBox(Vector2f(80vw, 15vh), L"", Vector2f(10vw, 20vh))),
	bPassword(states.r.fact.getTextBox(Vector2f(80vw, 15vh), L"", Vector2f(10vw, 37.5vh))),
	showPasswordButton(states.r.fact.getButton(Vector2f(37.5vw, 10vh), L"Показать", Vector2f(10vw, 57.5vh))),
	copyButton(states.r.fact.getButton(Vector2f(37.5vw, 10vh), L"Копировать", Vector2f(52.5vw, 57.5vh))),
	backButton(states.r.fact.getButton(Vector2f(70vw, 15vh), L"Назад", Vector2f(15vw, 75vh)))
{
	//showPasswordButton.getRect().setTextOffset(Vector2f(0, -0.5));
}

void States::PasswordBlank::refresh()
{
	if (states.currentBlank) {
		showPassword = false;
		bTitle.setString(states.currentBlank->title);
		bPassword.setString(wstring(states.currentBlank->password.getSize(), L'*'));
	}
}

void States::PasswordBlank::check(Event& event)
{
	showPasswordButton.check(event);
	copyButton.check(event);
	backButton.check(event);
	if (showPasswordButton.isClicked()) {
		showPassword = !showPassword;
		if (showPassword)
			bPassword.setString(states.currentBlank->password);
		else
			bPassword.setString(wstring(states.currentBlank->password.getSize(), L'*'));
	}
	else if (copyButton.isClicked()) {
		Clipboard::setString(states.currentBlank->password);
	}
	else if (backButton.isClicked()) {
		states.currentState = &states.chooseBlank;
		if (states.authorized)
			states.nextState = &states.passwordBlank;
		bTitle.setString(L"");
	}
}

void States::PasswordBlank::draw(RenderWindow& window)
{
	title.draw(window);
	bTitle.draw(window);
	bPassword.draw(window);
	showPasswordButton.draw(window);
	copyButton.draw(window);
	backButton.draw(window);
}

void States::PasswordBlank::update(RenderWindow& window, double elTime)
{
	title.draw(window);
	bTitle.draw(window);
	bPassword.draw(window);
	showPasswordButton.update(window);
	copyButton.update(window);
	backButton.update(window);
}

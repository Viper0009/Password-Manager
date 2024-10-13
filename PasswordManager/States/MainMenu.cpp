#include "States.h"
States::MainMenu::MainMenu(States& states) :
	states(states),
	title(states.r.fact.getTextBox(Vector2f(80vw, 20vh), L"Менеджер паролей", Vector2f(10vw, 10vh))),
	startButton(states.r.fact.getButton(Vector2f(35vw, 15vh), L"Начать", Vector2f(10vw, 75vh))),
	editorButton(states.r.fact.getButton(Vector2f(35vw, 15vh), L"Редактор", Vector2f(55vw, 75vh)))
{
	startButton.getRect().setTextOffset(Vector2f(0, -0.5));
}

void States::MainMenu::check(Event& event)
{
	title.check(event);
	startButton.check(event);
	editorButton.check(event);
	if (startButton.isClicked()) {
		switchState(states.chooseBlank);
		states.nextState = &states.enterPassword;
		states.chooseBlank.setStringButton(L"Прочитать");
	}
	if (editorButton.isClicked()) {
		switchState(states.editor);
	}
}

void States::MainMenu::draw(RenderWindow& window)
{
	title.draw(window);
	startButton.draw(window);
	editorButton.draw(window);
}

void States::MainMenu::update(RenderWindow& window, double elTime)
{
	title.draw(window);
	startButton.update(window);
	editorButton.update(window);
}

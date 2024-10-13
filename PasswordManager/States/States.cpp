#include "States.h"

void States::deleteBlank(int index)
{
	r.passwordList.erase(r.passwordList.begin() + index);
	r.timerList.erase(r.timerList.begin() + index);
	chooseBlank.blankButtons.erase(chooseBlank.blankButtons.begin() + index);
	editor.chooseBlank.blankButtons.erase(editor.chooseBlank.blankButtons.begin() + index);
}

void States::addBlank(const Blank& blank)
{
	r.passwordList.push_back(blank);
	r.timerList.push_back(0);
	chooseBlank.blankButtons.push_back(r.fact.getButton(Vector2f(70vw, 15vh), blank.title, Vector2f()));
	chooseBlank.setBlanksPosition(chooseBlank.pos);
	editor.chooseBlank.blankButtons.push_back(chooseBlank.blankButtons.back());
}

States::States(Resource& r) : r(r),
authorized(false),
currentBlankIndex(0),
currentState(&mainMenu),
currentBlank(nullptr),
nextState(nullptr),
intro(*this),
mainMenu(*this),
chooseBlank(*this),
enterPassword(*this),
answerQuestion(*this),
passwordBlank(*this),
confirmation(*this),
editor(*this)
{
	if (r.newClient) {
		currentState = &intro;
		intro.refresh();
	}
}

void States::check(Event & event)
{
	currentState->check(event);
}

void States::draw(RenderWindow& window)
{
	currentState->draw(window);
}

void States::update(RenderWindow& window, double elTime)
{
	currentState->update(window, elTime);
}

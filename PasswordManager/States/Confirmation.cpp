#include "States.h"

States::Confirmation::Confirmation(States& states) : states(states), _confirmed(false),
title(states.r.fact.getTextBox({70vw, 15vh}, L"Подтверждение", {15vw, 5vh})),
message(states.r.fact.getTextBox({80vw, 15vh}, L"Вы уверены в этом?", {10vw, 25vh})),
yes(states.r.fact.getButton({40vw, 15vh}, L"Да", {7.5vw, 80vh})),
no(states.r.fact.getButton({40vw, 15vh}, L"Нет", {52.5vw, 80vh})),
backState(nullptr), nextState(nullptr),
additiveBg(make_unique<RectangleShape>(Vector2f(ScreenSize)))
{
	additiveBg->setFillColor(states.r.colors.additiveBackground);
}

bool States::Confirmation::confirmed()
{
	bool ret = _confirmed;
	_confirmed = false;
	return ret;
}
void States::Confirmation::check(Event& event) {
	yes.check(event);
	no.check(event);
	if (yes.isClicked() || no.isClicked()) {
		_confirmed = yes.isClicked();
		if (_confirmed) {
			states.currentState = nextState;
			nextState->refresh();
		}
		else {
			states.currentState = backState;
			backState->refresh();
		}
	}
}
void States::Confirmation::draw(RenderWindow& window)
{
	title.draw(window);
	message.draw(window);
	yes.draw(window);
	no.draw(window);
}

void States::Confirmation::update(RenderWindow& window, double elTime)
{
	backState->draw(window);
	window.draw(*additiveBg);
	title.draw(window);
	message.draw(window);
	yes.update(window);
	no.update(window);
}

void States::Confirmation::refresh(State* backState, State* nextState, const String& message)
{
	this->message.setString(message);
	this->backState = backState;
	this->nextState = nextState;
	_confirmed = false;
}

void States::Confirmation::refresh() {
	message.setString(L"Вы уверены в этом?");
	_confirmed = false;
}
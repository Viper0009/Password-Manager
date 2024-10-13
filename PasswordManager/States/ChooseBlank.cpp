#include "States.h"
void States::ChooseBlank::setBlanksPosition(const Vector2f& pos)
{
	this->pos = pos;
	if (!blankButtons.empty()) {
		blankButtons[0].get().setPosition(pos);
	}
	for (int i = 1; i < blankButtons.size(); ++i) {
		blankButtons[i].get().setPosition(Vector2f(pos.x, 
			blankButtons[i - 1].get().getPosition().y + blankButtons[i].get().getGlobalBounds().height * 1.25));
	}
}
FloatRect States::ChooseBlank::getBlanksGlobalBounds() const
{
	if (!blankButtons.empty())
		return
		FloatRect(pos, Vector2f(
			blankButtons.front().get().getGlobalBounds().width,
			blankButtons.front().get().getGlobalBounds().height * blankButtons.size() + blankButtons.front().get().getGlobalBounds().height * 0.25 * (blankButtons.size() - 1)));
	else
		return FloatRect(pos, Vector2f());
}
States::ChooseBlank::ChooseBlank(States& states) : states(states), mouseInRect(false),
title(states.r.fact.getTextBox(Vector2f(80vw, 20vh), L"Выберите бланк с паролем", Vector2f(10vw, 5vh))),
border(Vector2f(100vw, 30vh)),
readButton(states.r.fact.getButton(Vector2f(50vw, 15vh), L"...", Vector2f(10vw, 80vh))),
backButton(states.r.fact.getButton(Vector2f(25vw, 15vh), L"Назад", Vector2f(65vw, 80vh)))
{
	readButton.setEnable(false);
	border.setFillColor(states.r.colors.background);
	for (auto& i : states.r.passwordList) {
		blankButtons.push_back(states.r.fact.getButton(Vector2f(70vw, 15vh), i.title, Vector2f()));
	}
	this->setBlanksPosition(defaultPosition);
}

void States::ChooseBlank::setStringButton(const sf::String& str)
{
	readButton.getRect().setString(str);
}

const sf::String& States::ChooseBlank::getStringButton() const
{
	return readButton.getRect().getString();
}

void States::ChooseBlank::refresh()
{
	setBlanksPosition(defaultPosition);
	readButton.setEnable(false);
}

void States::ChooseBlank::check(Event& event)
{
	for(auto& i : blankButtons)
		i.get().check(event);
	readButton.check(event);
	backButton.check(event);
	if (event.type == Event::MouseButtonPressed ||
		event.type == Event::MouseButtonReleased) {
		bool clicked = false;
		for (int i = 0; i < blankButtons.size(); ++i) {
			auto& iBlankButton = blankButtons[i];
			clicked = clicked || iBlankButton.get().isClicked() && mouseInRect;
			if (iBlankButton.get().isClicked() && mouseInRect) {
				states.currentBlank = &states.r.passwordList[i];
				states.currentBlankIndex = i;
			}
		}
		if (event.type == Event::MouseButtonReleased) {
			clicked = clicked || (readButton.isClicked() && readButton.getEnable());
			readButton.setEnable(clicked);
		}
		if (readButton.isClicked()) {
			if (!states.authorized)
				states.currentState = states.nextState;
			else
				states.currentState = &states.passwordBlank;
			states.currentState->refresh();
		}
		if (backButton.isClicked()) {
			states.currentState = &states.mainMenu;
		}
	}
	if (event.type == Event::MouseWheelScrolled && !blankButtons.empty()) {
		Vector2f newPos(pos);
		newPos.y += event.mouseWheelScroll.delta * 5vh;
		if (blankButtons.size() >= 3) {
			if (newPos.y < defaultPosition.y - getBlanksGlobalBounds().height + blankListRectSize.y)
				setBlanksPosition(Vector2f(defaultPosition.x, defaultPosition.y - getBlanksGlobalBounds().height + blankListRectSize.y));
			else if (newPos.y > defaultPosition.y)
				setBlanksPosition(defaultPosition);
			else
				setBlanksPosition(newPos);
		}
		else
			setBlanksPosition(defaultPosition);
	}
	
}

void States::ChooseBlank::draw(RenderWindow& window)
{
	for (auto& i : blankButtons) {
		i.get().draw(window);
	}
	border.setPosition(Vector2f());
	window.draw(border);
	border.setPosition(Vector2f(0vw, 75vh));
	window.draw(border);
	readButton.draw(window);
	backButton.draw(window);
	title.draw(window);
}

void States::ChooseBlank::update(RenderWindow& window, double elTime)
{
	mouseInRect = FloatRect(defaultPosition, blankListRectSize).contains(window.mapPixelToCoords(Mouse::getPosition(window)));
	if (mouseInRect)
		for (auto& i : blankButtons) {
			i.get().update(window);
		}
	else
		for (auto& i : blankButtons)
			i.get().draw(window);
	border.setPosition(Vector2f());
	window.draw(border);
	border.setPosition(Vector2f(0vw, 75vh));
	window.draw(border);
	readButton.update(window);
	backButton.update(window);
	title.draw(window);
}

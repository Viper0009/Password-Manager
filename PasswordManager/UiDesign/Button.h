#pragma once
#include "UiDesign.h"
#include "Drawer.h"
#include "Checker.h"
template<typename Rectangle>
class Button
{
protected:
	Rectangle _rect;
	bool _intersected, _pressed, _released, _clicked, _enable;
	Color _highlightColor, _onClickColor, _defaultColor, _disableColor;
public:
	Button() : _intersected(), _pressed(), _released(), _clicked(), _enable(false),
		_highlightColor(Color::White), _onClickColor(Color::White), _defaultColor(Color::White)
	{}
	Button(const Rectangle& rect, Color highlightColor, Color onClickColor, Color disableColor/* = Color::White*/) : 
		_rect(rect), _intersected(), _pressed(), _released(), _clicked(), _enable(true),
		_highlightColor(highlightColor),
		_onClickColor(onClickColor), _defaultColor(rect.getFillColor()), _disableColor(disableColor)
	{}
	Button(const Button& button) : Button(button._rect, button._highlightColor, button._onClickColor, button._defaultColor) 
	{}

	void setPosition(Vector2f pos) {
		_rect.setPosition(pos);
	}
	Vector2f getPosition() const {
		return _rect.getPosition();
	}
	FloatRect getGlobalBounds() const {
		return _rect.getGlobalBounds();
	}
	void setSize(Vector2f sz) {
		_rect.setSize(sz);
	}
	Vector2f getSize() const {
		return _rect.getSize();
	}
	void setFillColor(Color col) {
		_defaultColor = col;
	}
	Color getFillColor() const {
		return _defaultColor;
	}
	Rectangle& getRect() {
		return _rect;
	}
	void setEnable(bool enable) {
		_enable = enable;
	}
	bool getEnable() const {
		return _enable;
	}
	void check(Event& event) {
		if (_enable) {
			_pressed = _pressed ||
				(_intersected &&
					event.type == Event::MouseButtonPressed &&
					event.mouseButton.button == Mouse::Button::Left);
			_released = (event.type == Event::MouseButtonReleased);
			_clicked = _pressed && _released && _intersected;
			_pressed = _pressed && !_released;
			Checker::check(_rect, event);
			_rect.setFillColor(_defaultColor);
		}
		else
			_clicked = false;
	}
	// Put this function in the body of event handler
	// @return true if this button has been clicked
	bool isClicked() {
		return _clicked;
	}
	bool isIntersected() {
		return _intersected;
	}
	void update(RenderWindow& window){
		_intersected = _rect.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)));
		if (_enable) {
			if (_pressed) {
				_rect.setFillColor(_onClickColor);
			}
			else if (_intersected) {
				_rect.setFillColor(_highlightColor);
			}
			else {
				_rect.setFillColor(_defaultColor);
			}
		}
		else {
			_rect.setFillColor(_disableColor);
		}
		draw(window);
	}
	void draw(RenderWindow& window) {
		Drawer::draw(_rect, window);
	}
};

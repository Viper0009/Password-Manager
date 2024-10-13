#include "InputTextBox.h"
#include "iostream"
InputTextBox::InputTextBox(Align al) : TextBox(al), _intersected(), _textTyping(), _baseStringColor(Color::Black), _textColor(Color::Black){

}
InputTextBox::InputTextBox(Vector2f _size, Vector2f _pos, Align al) : TextBox(_size, _pos, al), _intersected(), _textTyping(), _baseStringColor(Color::Black), _textColor(Color::Black){

}
InputTextBox::InputTextBox(Vector2f _size, Align al) : TextBox(_size, al), _intersected(), _textTyping(), _baseStringColor(Color::Black), _textColor(Color::Black) {

}
void InputTextBox::check(Event& event){
	if (event.type == Event::MouseButtonPressed) {
		bool typed = _textTyping;
		_textTyping = _intersected && event.mouseButton.button == Mouse::Button::Left;
		_inputString.setTypingEnabled(_textTyping);
		if (_textTyping && !typed) {
			String str = _inputString.getString() + L'|';
			_text.setString(str);
			_text.setFillColor(_textColor);
			align();
		}
		else if (!_textTyping && typed && !_inputString.getString().isEmpty()) {
			_text.setString(_inputString.getString());
			_text.setFillColor(_textColor);
			align();
		}
		else if (!_textTyping && _inputString.getString().isEmpty()) {
			_text.setFillColor(_baseStringColor);
			_text.setString(_baseString);
			align();
		}
	}
	_inputString.check(event);
	if (event.type == Event::TextEntered && _textTyping) {
		if (event.text.unicode == 13) { // 13 - endline ('\n') 
			_inputString.setTypingEnabled(_textTyping = false);
			if (_inputString.getString().isEmpty()) {
				_text.setFillColor(_baseStringColor);
				_text.setString(_baseString);
			}
			else
				_text.setString(_inputString.getString());
			align();
			return;
		}
		_text.setString(_inputString.getString() + L'|');
		align();
	}
}
void InputTextBox::setBaseString(const sf::String& str) {
	_baseString = str;
	if (!_textTyping && _inputString.getString().isEmpty()) {
		_text.setString(_baseString);
	}
}
const sf::String& InputTextBox::getBaseString() const {
	return _baseString;
}
void InputTextBox::setBaseStringFillColor(Color col) { 
	_baseStringColor = col; 
	if (!_textTyping && _inputString.getString().isEmpty()) {
		_text.setFillColor(_baseStringColor);
		_text.setString(_baseString);
	}
}
Color InputTextBox::getBaseStringFillColor() const { return _baseStringColor; }
void InputTextBox::setTextFillColor(Color col)
{
	_textColor = col;
}
Color InputTextBox::getTextFillColor() const
{
	return _textColor;
}
void InputTextBox::setString(const sf::String& str)
{
	_inputString.setString(str);
	if (!_textTyping && _inputString.getString().isEmpty()) {
		_text.setFillColor(_baseStringColor);
		_text.setString(_baseString);
	}
	else
		_text.setString(str);
	align();
}
const sf::String& InputTextBox::getString() const {
	return _inputString.getString();
}
void InputTextBox::setStringSizeLimit(const size_t& lim)
{
	_inputString.setStringSizeLimit(lim);
}
const size_t& InputTextBox::getStringSizeLimit() const
{
	return _inputString.getStringSizeLimit();
}
void InputTextBox::setTypingEnabled(bool ie) { _inputString.setTypingEnabled(ie); _textTyping = ie; }
bool InputTextBox::getTypingEnabled() const { return _inputString.getTypingEnabled(); }
void InputTextBox::draw(RenderWindow& window) const {
	_intersected = getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)));
	TextBox::draw(window);
}
void InputTextBox::update(RenderWindow& window) {
	draw(window);
}

bool InputTextBox::isIntersected() const
{
	return _intersected;
}

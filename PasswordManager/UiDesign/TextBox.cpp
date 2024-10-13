#include "TextBox.h"

void TextBox::align()
{
	_box.setPosition(_pos);
	_box.setSize(_size);
	_box.setScale(1, 1);
	_text.setScale(1, 1);
	FloatRect boxRect = _box.getGlobalBounds();
	int strCount = boxRect.height * 0.9 / _text.getGlobalBounds().height;
	if (strCount > 1 && _text.getGlobalBounds().width > boxRect.width) {
		float charSize = _text.getGlobalBounds().width / _text.getString().getSize();
		int charsPerStr = boxRect.width * 0.9 / charSize;

		String textStr;
		std::wstring tempStr2;
		std::wstring tempStr = _text.getString();
		std::copy_if(tempStr.begin(), tempStr.end(), std::back_inserter(tempStr2), [](const wchar_t& ch) { return ch != L'\n'; });
		textStr = tempStr2;
		if (charsPerStr) {
			for (int i = charsPerStr - 1, i0 = 0; i < textStr.getSize() - 1; i0 = i, i += charsPerStr) {
				for (int j = i; j >= i0; --j) {
					if (textStr[j] == L' ') {
						i = j + 1;
						break;
					}
				}
				textStr.insert(i, '\n');
			}
			_text.setString(textStr);
		}
	}
	if (_text.getGlobalBounds().width > boxRect.width * 0.9) {
		float scale = boxRect.width * 0.9 / _text.getGlobalBounds().width;
		_text.setScale(scale, scale);
	}
	if (_text.getGlobalBounds().height > boxRect.height * 0.9) {
		float scale = boxRect.height * 0.9 / _text.getGlobalBounds().height;
		_text.setScale(_text.getScale().x * scale, _text.getScale().y * scale);
	}
	_text.setScale(_text.getScale().x * _scale.x, _text.getScale().y * _scale.y);
	_box.setScale(_scale);
	switch (_textAlign) {
	case Align::Center: {
		_text.setPosition(
			_pos.x + boxRect.width * 0.5 - _text.getGlobalBounds().width * (0.5 - _textOffset.x),
			_pos.y + boxRect.height * 0.5 - _text.getGlobalBounds().height * (0.5 - _textOffset.y));
	} break;
	case Align::Left: {
		_text.setPosition(_pos.x + boxRect.width * 0.05 + _text.getGlobalBounds().width * _textOffset.x,
			_pos.y + boxRect.height * 0.05 + _text.getGlobalBounds().height * _textOffset.y);
	} break;
	}
}

TextBox::TextBox(Align al) : _size(), _pos(), _scale(1, 1), _textOffset(), _textAlign(al) {}
TextBox::TextBox(Vector2f _size, Vector2f _pos, Align al) : _size(_size), _pos(_pos), _scale(1, 1), _textOffset(), _textAlign(al) { setSize(_size); }
TextBox::TextBox(Vector2f _size, Align al) : _size(_size), _pos(), _scale(1, 1), _textOffset(), _textAlign(al) { setSize(_size); }

void TextBox::setPosition(const Vector2f& _pos){
	this->_pos = _pos;
	align();
}
const Vector2f& TextBox::getPosition() const{
	return _pos;
}
void TextBox::setScale(const Vector2f& _scale) {
	this->_scale = _scale;
}
const Vector2f& TextBox::getScale() const {
	return _scale;
}
void TextBox::setSize(const Vector2f& _size) {
	this->_size = _size;
	align();
}
const Vector2f& TextBox::getSize() const {
	return _size;
}
void TextBox::setBoxFillColor(const Color& color) {
	_box.setFillColor(color);
}
const Color& TextBox::getBoxFillColor() const {
	return _box.getFillColor();
}
void TextBox::setTextFillColor(const Color& color) {
	_text.setFillColor(color);
}
const Color& TextBox::getTextFillColor() const {
	return _text.getFillColor();
}
void TextBox::setCharacterSize(const uint32_t& cs) {
	_text.setCharacterSize(cs);
	align();
}
const uint32_t& TextBox::getCharacterSize() const {
	return _text.getCharacterSize();
}
void TextBox::setString(const sf::String& str) {
	_text.setString(str);
	align();
}
const sf::String& TextBox::getString() const {
	return _text.getString();
}
void TextBox::setFont(const sf::Font& font) {
	_text.setFont(font);
	align();
}
const sf::Font* TextBox::getFont() const {
	return _text.getFont();
}
void TextBox::setText(const sf::Text& text) {
	_text = text;
	align();
}
const Text& TextBox::getText() const {
	return _text;
}
void TextBox::setStyle(const Uint32 style)
{
	_text.setStyle(style);
}
const Uint32 TextBox::getStyle() const
{
	return _text.getStyle();
}
void TextBox::setFillColor(const Color& color)
{
	_box.setFillColor(color);
}
const Color& TextBox::getFillColor() const
{
	return _box.getFillColor();
}
const FloatRect TextBox::getGlobalBounds() const
{
	return _box.getGlobalBounds();
}
void TextBox::setAlign(const Align& al) {
	_textAlign = al;
	align();
}
const Align& TextBox::getAlign() const {
	return _textAlign;
}
void TextBox::setTextOffset(const Vector2f& offset) { 
	_textOffset = offset;
	align();
}
const Vector2f& TextBox::getTextOffset() const { return _textOffset; }
void TextBox::draw(RenderWindow& window) const{
	window.draw(_box);
	window.draw(_text);
}

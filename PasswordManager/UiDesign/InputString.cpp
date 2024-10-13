#include "InputString.h"
#include "iostream"
InputString::InputString() : _str(), _typingEnabled(), _stringSizeLimit(ULLONG_MAX) {}
void InputString::check(Event& event) {
	if (_typingEnabled) {
		if (event.type == Event::TextEntered) {
			if (event.text.unicode == 8) {
				if (_str.getSize())
					_str.erase(_str.getSize() - 1, 1);
			}
			else if (event.text.unicode == 127) {
				int index = 0;
				for (int i = _str.getSize() - 1; i > 0; --i) {
					if (_str[i] == L' ' || _str[i] == L'\t') {
						index = i;
						break;
					}
				}
				_str.erase(index, _str.getSize() - index);
			}
			else if (_str.getSize() < _stringSizeLimit) {
				if (event.text.unicode == 22) { // ctrl + v
					_str += Clipboard::getString();
					if (_str.getSize() > _stringSizeLimit)
						_str.erase(_stringSizeLimit, _str.getSize() - _stringSizeLimit);
				}
				else if (event.text.unicode != 13) {
					_str += event.text.unicode;
				}
			}
		}
	}
}
void InputString::setTypingEnabled(bool typingEnabled){
	_typingEnabled = typingEnabled;
}
bool InputString::getTypingEnabled() const
{
    return _typingEnabled;
}
void InputString::setString(const String& str) {
	_str = str;
}
void InputString::setStringSizeLimit(const size_t limit)
{
	_stringSizeLimit = limit;
}
const size_t InputString::getStringSizeLimit() const
{
	return _stringSizeLimit;
}
const String& InputString::getString() const {
	return _str;
}
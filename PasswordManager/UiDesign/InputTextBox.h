#pragma once
#include "UiDesign.h"
#include "InputString.h"
#include "TextBox.h"
#include "Checker.h"
class InputTextBox : public TextBox {
private:
	InputString _inputString;
	mutable bool _intersected, _textTyping;
	sf::String _baseString;
	Color _baseStringColor, _textColor;
public:
	InputTextBox(Align al = Align::Center);
	InputTextBox(Vector2f _size, Vector2f _pos, Align al = Align::Center);
	InputTextBox(Vector2f _size, Align al = Align::Center);

	void setTypingEnabled(bool ie);
	bool getTypingEnabled() const;
	void setBaseString(const sf::String& str);
	const sf::String& getBaseString() const;
	void setBaseStringFillColor(Color col);
	Color getBaseStringFillColor() const;
	void setTextFillColor(Color col);
	Color getTextFillColor() const;
	void setString(const sf::String& str);
	const sf::String& getString() const;
	void setStringSizeLimit(const size_t& lim);
	const size_t& getStringSizeLimit() const;
	void check(Event& event);
	virtual void draw(RenderWindow& window) const override;
	void update(RenderWindow& window);
	bool isIntersected() const;
};
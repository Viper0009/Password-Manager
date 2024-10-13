#pragma once
#include "UiDesign.h"
#include "Checker.h"
#include "Drawer.h"
#include "Checker.h"
enum Align {
	Center,
	Left
};
class TextBox : public SelfDrawable, public Checkable
{
protected:
	mutable Text _text;
	RectangleShape _box;
	Vector2f _pos;
	Vector2f _size;
	Vector2f _scale;
	Align _textAlign;
	void align();
	Vector2f _textOffset;
public:
	TextBox(Align al = Align::Center);
	TextBox(Vector2f _size, Vector2f _pos, Align al = Align::Center);
	TextBox(Vector2f _size, Align al = Align::Center);

	void setPosition(const Vector2f& _pos);
	const Vector2f& getPosition() const;
	void setScale(const Vector2f& _scale);
	const Vector2f& getScale() const;
	void setSize(const Vector2f& _size);
	const Vector2f& getSize() const;
	// @param color: new color of the rectangle
	void setBoxFillColor(const Color& color);
	// @return color of the rectangle
	const Color& getBoxFillColor() const;
	// @param color: new color of the text
	void setTextFillColor(const Color& color);
	// @return color of the text
	const Color& getTextFillColor() const;
	void setCharacterSize(const uint32_t& cs);
	const uint32_t& getCharacterSize() const;
	void setString(const sf::String& str);
	const sf::String& getString() const;
	void setFont(const sf::Font& font);
	const sf::Font* getFont() const;
	void setText(const sf::Text& text);
	const Text& getText() const;
	void setStyle(const Uint32 style);
	const Uint32 getStyle() const;
	void setFillColor(const Color& color);
	// Same as getBoxFillColor()
	// @return color of the rectangle
	const Color& getFillColor() const;
	// @return global bounds of the rectangle
	const FloatRect getGlobalBounds() const;
	void setAlign(const Align& al);
	const Align& getAlign() const;
	void setTextOffset(const Vector2f& offset);
	const Vector2f& getTextOffset() const;
	virtual void draw(RenderWindow& window) const override;
};


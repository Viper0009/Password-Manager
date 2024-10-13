#pragma once
#include "Header.h"
class Factory
{
private:
	Fonts& _fonts;
	Colors& _colors;
	std::vector<std::unique_ptr<TextBox>> _textBoxes;
	std::vector<std::unique_ptr<Button<InputTextBox>>> _inputTextBoxes;
	std::vector<std::unique_ptr<Button<TextBox>>> _buttons;
	TextBox& makeTextBox(Vector2f sz, const String& str, Vector2f pos);
	Button<InputTextBox>& makeButtonInputTextBox(Vector2f sz, const String& str, Vector2f pos);
	Button<InputTextBox>& makeTitleButtonInputTextBox(Vector2f sz, const String& str, Vector2f pos);
	Button<TextBox>& makeButton(Vector2f sz, const String& str, Vector2f pos);
public:
	Factory(Fonts& fonts, Colors& colors);
	TextBox& getTextBox(Vector2f sz, Vector2f pos = Vector2f());
	TextBox& getTextBox(Vector2f sz, const String& str, Vector2f pos = Vector2f());

	Button<InputTextBox>& getInputTextBox(Vector2f sz, const String& baseString, Vector2f pos = Vector2f());
	Button<InputTextBox>& getTitleInputTextBox(Vector2f sz, const String& baseString, Vector2f pos = Vector2f());

	Button<TextBox>& getButton(Vector2f sz, const String& str, Vector2f pos = Vector2f());
};

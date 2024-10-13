#include "Factory.h"

TextBox& Factory::makeTextBox(Vector2f sz, const String& str, Vector2f pos)
{
	_textBoxes.push_back(make_unique<TextBox>(sz, pos, Align::Center));
	TextBox& textBox = *_textBoxes.back();
	textBox.setFont(_fonts.basic);
	textBox.setBoxFillColor(_colors.textBoxFill);
	textBox.setTextFillColor(_colors.textBoxText);
	textBox.setString(str);
	textBox.setTextOffset(Vector2f(0, -0.25));
	textBox.setCharacterSize(50px);
	return textBox;
}

Button<InputTextBox>& Factory::makeButtonInputTextBox(Vector2f sz, const String& str, Vector2f pos)
{
	auto inputTextBox = make_unique<InputTextBox>(sz, pos, Align::Left);
	inputTextBox->setFont(_fonts.basic);
	inputTextBox->setBaseStringFillColor(_colors.inputTextBoxBaseString);
	inputTextBox->setBaseString(str);
	inputTextBox->setTextFillColor(_colors.inputTextBoxText);
	inputTextBox->setBoxFillColor(_colors.inputTextBoxFill);
	inputTextBox->setTextOffset(Vector2f(0, 0));
	inputTextBox->setCharacterSize(30px);
	_inputTextBoxes.push_back(make_unique<Button<InputTextBox>>(
		*inputTextBox, _colors.inputTextBoxHighLight, _colors.inputTextBoxOnClick, _colors.inputTextBoxDisable)
	);
	Button<InputTextBox>& buttonInputTextBox = *_inputTextBoxes.back();
	return buttonInputTextBox;
}

Button<InputTextBox>& Factory::makeTitleButtonInputTextBox(Vector2f sz, const String& str, Vector2f pos)
{
	auto& a = makeButtonInputTextBox(sz, str, pos).getRect();
	a.setAlign(Align::Center);
	a.setTextOffset(Vector2f(0, -0.25));
	return *_inputTextBoxes.back();
}

Button<TextBox>& Factory::makeButton(Vector2f sz, const String& str, Vector2f pos)
{
	_buttons.push_back(
		std::make_unique<Button<TextBox>>(TextBox(sz, pos, Align::Center), _colors.buttonHighlight, _colors.buttonOnClick, _colors.buttonDisable)
	);
	auto& button = *_buttons.back();
	button.setPosition(pos);
	auto& tbox = button.getRect();
	tbox.setBoxFillColor(_colors.buttonFill);
	tbox.setTextFillColor(_colors.buttonText);
	tbox.setFont(_fonts.basic);
	tbox.setString(str);
	tbox.setCharacterSize(50px);
	tbox.setTextOffset(Vector2f(0, -0.25));
	return button;
}

Factory::Factory(Fonts& fonts, Colors& colors) :
	_fonts(fonts), _colors(colors)
{
}

TextBox& Factory::getTextBox(Vector2f sz, Vector2f pos)
{
	return makeTextBox(sz, String(), pos);
}

TextBox& Factory::getTextBox(Vector2f sz, const String& str, Vector2f pos)
{
	return makeTextBox(sz, str, pos);
}

Button<InputTextBox>& Factory::getInputTextBox(Vector2f sz, const String& baseString, Vector2f pos)
{
	return makeButtonInputTextBox(sz, baseString, pos);
}

Button<InputTextBox>& Factory::getTitleInputTextBox(Vector2f sz, const String& baseString, Vector2f pos)
{
	return makeTitleButtonInputTextBox(sz, baseString, pos);
}

Button<TextBox>& Factory::getButton(Vector2f sz, const String& str, Vector2f pos)
{
	return makeButton(sz, str, pos);
}

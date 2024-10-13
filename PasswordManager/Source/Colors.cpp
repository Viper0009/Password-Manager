#include "Colors.h"

void Colors::init1()
{
	// this->background = Color(220, 220, 220);
	this->background = Color(235, 235, 235);
	this->additiveBackground = Color(background.r, background.g, background.b, 180);
	this->buttonHighlight = Color(240, 249, 255);
	this->buttonOnClick = Color(233, 242, 247);
	this->buttonFill = Color(247, 252, 255);
	this->buttonText = Color::Black;
	this->buttonDisable = Color(220, 220, 220);
	this->textBoxFill = Color(238, 255, 255);
	this->textBoxText = Color::Black;
	this->inputTextBoxBaseString = Color(120, 120, 120);
	this->inputTextBoxFill = Color::White;
	this->inputTextBoxText = Color::Black;
	this->inputTextBoxHighLight = Color(250, 250, 250);
	this->inputTextBoxOnClick = Color(245, 245, 245);
	this->inputTextBoxDisable = Color(220, 220, 220);
	this->outputText = Color(39, 97, 163);
}

Colors::Colors()
{
	init1();
}

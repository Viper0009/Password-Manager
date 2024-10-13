#pragma once
#include "UiDesign.h"

class InputString
{
private:
	String _str;
	bool _typingEnabled;
	size_t _stringSizeLimit;
public:
	InputString();
	void check(Event& event);
	void setTypingEnabled(bool typingEnabled);
	bool getTypingEnabled() const;
	void setString(const String& str);
	void setStringSizeLimit(const size_t limit);
	const size_t getStringSizeLimit() const;
	const String& getString() const;
};


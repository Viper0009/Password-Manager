#pragma once
#include "Header.h"
#include "Factory.h"
class Resource
{
private:
	void init();
public:
	Fonts fonts;
	Colors colors;
	Cursors curs;
	Factory fact;
	Encryptor enc;
	vector<Blank> passwordList;
	vector<time_t> timerList;
	sf::String mainPassword;
	bool newClient;
	Resource();
	~Resource();
};


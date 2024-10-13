#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Encryptor
{
private:
	int32_t _k;
public:
	Encryptor(const int32_t& key);
	void setKey(const int32_t& key);
	sf::String encrypt(const sf::String& str);
	sf::String decrypt(const sf::String& str);
};


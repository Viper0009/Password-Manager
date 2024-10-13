#pragma once
#include "vector"
#include "fstream"
#include "SFML/System/String.hpp"
#include "iostream"
#include "Logging.h"
#include "Blank.h"
#include "sstream"
class FileReader
{
private:
	std::wfstream file;
public:
	int getEncryptKey();
	std::vector<Blank> getPasswordList();
	sf::String getMainPassword();
	std::vector<time_t> getTime();
	void setEncryptKey(const int32_t& key);
	void setPasswordList(const std::vector<Blank>& passwordList);
	void setParams(const int32_t& key, const sf::String& mainPass);
	void setTime(const std::vector<time_t>& timerList);
};


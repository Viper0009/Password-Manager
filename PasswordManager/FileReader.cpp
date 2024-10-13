#include "FileReader.h"
static std::wostream& operator<<(std::wostream& os, const sf::String& str) {
	if (!str.isEmpty())
		os << str[0];
	for (size_t i = 1; i < str.getSize(); ++i)
		os << L" " << str[i];
	os << L" ;";
	return os;
}

static std::wistream& operator>>(std::wistream& is, sf::String& str) {
	std::vector<sf::Uint32> ustr;
	std::wstring wstr;
	is >> wstr;
	while (wstr != L";" && !wstr.empty() && wstr != L"\n" && !is.eof()) {
		ustr.push_back(std::stoi(wstr));
		is >> wstr;
	}
	str = sf::String::fromUtf32(ustr.begin(), ustr.end());
	return is;
}

int FileReader::getEncryptKey()
{
	int encryptKey{};
	file.open("params", std::wfstream::in);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG("EncryptKey in: \"params\" file open failed!");
#endif
	}
	else {
		std::wstring temp;
		std::getline(file, temp);
		if (!temp.empty())
			encryptKey = std::stoi(temp);
		else
			encryptKey = 0;
#ifdef DEBUG
		INFO_LOG_IF("EncryptKey in: data load done", file.eof() && !temp.empty());
		else ER_LOG("EncryptKey in: data load failed");
#endif 
		file.close();
	}
	return encryptKey;
}

std::vector<Blank> FileReader::getPasswordList()
{
	std::vector<Blank> pList;
	file.open("data", std::wfstream::in);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG("PasswordList in: \"data\" file open failed!");
#endif
	}
	else {
		while (!file.eof()) {
			QuestionAnswersContainer rightAnswers, wrongAnswers;
			sf::String title, password, question;
			std::wstring rightAnswersStr, wrongAnswersStr;
			std::wstring questionType;
			file >> title >> password >> question;
			file.ignore();
			getline(file, questionType);
			getline(file, rightAnswersStr);
			getline(file, wrongAnswersStr);
			std::wstringstream strin(rightAnswersStr, std::wstringstream::in);
			while (!strin.eof()) {
				sf::String str1;
				strin >> str1;
				if (!str1.isEmpty())
					rightAnswers.push_back(str1);
				strin.ignore(3);
			}
			std::wstringstream strin1(wrongAnswersStr, std::wstringstream::in);
			while (!strin1.eof()) {
				sf::String str1;
				strin1 >> str1;
				if (!str1.isEmpty())
					wrongAnswers.push_back(str1);
				strin1.ignore(3);
			}
			if (!password.isEmpty() && !title.isEmpty() && !questionType.empty())
				pList.push_back(Blank(title, password, Question(question, rightAnswers, wrongAnswers), Question::Type(std::stoi(questionType))));
		}
#ifdef DEBUG
		INFO_LOG_IF("PasswordList in: data load done", file.eof());
#endif 
		file.close();
	}
	return pList;
}

sf::String FileReader::getMainPassword()
{
	sf::String ret;
	file.open("params", std::wfstream::in);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG("MainPassword in: open file failed!");
#endif
	}
	else {
		std::wstring temp;
		std::getline(file, temp);
		if(!file.eof())
			file >> ret;
		file.close();
#ifdef DEBUG
		INFO_LOG_IF("MainPassword in: load data done", !ret.isEmpty());
		else ER_LOG("MainPassword in: load data failed");
#endif
	}
	return ret;
}

std::vector<time_t> FileReader::getTime()
{
	std::vector<time_t> timeList;
	file.open(L"chronos", std::wfstream::in);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG(L"Time in: open file failed!");
#endif
	}
	else {
		std::wstring tempL;
		while (!file.eof()) {
			std::getline(file, tempL);
			if(!tempL.empty())
				timeList.push_back(std::stoll(tempL));
		}
#ifdef DEBUG
		INFO_LOG_IF("Time in: load data done", file.eof());
#endif
	}
	return timeList;
}

void FileReader::setEncryptKey(const int32_t& key)
{
	file.open("params", std::wfstream::out);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG("EncryptKey out: \"params\" file open failed!");
#endif 
	}
	else {
		file << key;
#ifdef DEBUG
		INFO_LOG_IF("EncryptKey out: data save done", file.good());
#endif 
		file.close();
	}
}

void FileReader::setPasswordList(const std::vector<Blank>& passwordList)
{
	file.open("data", std::wfstream::out);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG("PasswordList out: \"data\" file open failed!");
#endif 
	}
	else {
		for (auto& i : passwordList) {
			file << (i.title) << std::endl;
			file << (i.password) << std::endl;
			file << (i.q.question) << std::endl;
			file << i.qt << std::endl;
			for (auto& j : i.q.rightAnswers) {
				file << (j) << L" , ";
			}
			file << std::endl;
			for (auto& j : i.q.wrongAnswers) {
				file << (j) << L" , ";
			}
			file << std::endl;
		}
#ifdef DEBUG
		INFO_LOG_IF("PasswordList out: data save done", file.good());
		else INFO_LOG_IF("PasswordList out: data save has an error", file.bad());
#endif 
		file.close();
	}
}

void FileReader::setParams(const int32_t& key, const sf::String& mainPass)
{
	file.open("params", std::wfstream::out);
	if (!file.is_open()) {
#ifdef DEBUG
		ER_LOG("Params out: file open failed!");
#endif
	}
	else {
		file << key << std::endl;
		file << mainPass << std::endl;
#ifdef DEBUG
		INFO_LOG_IF("Params out: save data done", file.good());
		else ER_LOG("Params out: save data failed");
#endif
		file.close();
	}
}

void FileReader::setTime(const std::vector<time_t>& timerList)
{
	file.open(L"chronos", std::wfstream::out);
	if(!file.is_open()) {
#ifdef DEBUG
		ER_LOG(L"Time out: file open failed");
#endif
	}
	else {
		for (auto& i : timerList) {
			file << i << std::endl;
		}
#ifdef DEBUG
		INFO_LOG_IF("Time out: save data done", file.good());
#endif
	}
}

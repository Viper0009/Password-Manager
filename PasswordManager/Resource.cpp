#include "Resource.h"

void Resource::init()
{
	auto fr = make_unique<FileReader>();
	this->enc.setKey(fr->getEncryptKey());
	vector<Blank> encryptedPasswordList(fr->getPasswordList());
	this->passwordList.reserve(encryptedPasswordList.size());
	for (auto& i : encryptedPasswordList) {
		QuestionAnswersContainer
			decryptedRightAnswers,
			decryptedWrongAnswers;
		for (auto& j : i.q.rightAnswers)
			decryptedRightAnswers.push_back(enc.decrypt(j));
		for (auto& j : i.q.wrongAnswers)
			decryptedWrongAnswers.push_back(enc.decrypt(j));
		this->passwordList.push_back(Blank(enc.decrypt(i.title), enc.decrypt(i.password),
			Question(enc.decrypt(i.q.question), decryptedRightAnswers, decryptedWrongAnswers), i.qt));
	}
	mainPassword = enc.decrypt(fr->getMainPassword());
	this->timerList = fr->getTime();
	newClient = mainPassword.isEmpty();
	if (newClient) {
		passwordList.clear();
		int encrKey = fr->getEncryptKey();
		if (!encrKey)
			encrKey = rand() % 50 + 50;
		fr->setEncryptKey(encrKey);
		enc.setKey(encrKey);
	}
}

Resource::Resource() : fact(fonts, colors), enc(0)
{
	init();
}

Resource::~Resource()
{
	auto fr = make_unique<FileReader>();
	for (auto& i : passwordList) {
		i.title = enc.encrypt(i.title);
		i.password = enc.encrypt(i.password);
		i.q.question = enc.encrypt(i.q.question);
		QuestionAnswersContainer
			encryptedRightAnswers,
			encryptedWrongAnswers;
		for (auto& j : i.q.rightAnswers)
			encryptedRightAnswers.push_back(enc.encrypt(j));
		for (auto& j : i.q.wrongAnswers)
			encryptedWrongAnswers.push_back(enc.encrypt(j));
		i.q.rightAnswers = encryptedRightAnswers;
		i.q.wrongAnswers = encryptedWrongAnswers;
	}
	fr->setPasswordList(passwordList);
	fr->setParams(fr->getEncryptKey(), enc.encrypt(mainPassword));
	fr->setTime(this->timerList);
}

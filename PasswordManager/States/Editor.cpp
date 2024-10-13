#include "States.h"
States::Editor::EnterPassword::EnterPassword(States& states) : states(states),
title(states.r.fact.getTextBox(Vector2f(80vw, 20vh), L"Авторизация", Vector2f(10vw, 5vh))),
input(states.r.fact.getInputTextBox(Vector2f(70vw, 20vh), L"Введите пароль", Vector2f(15vw, 35vh))),
output(states.r.fact.getTextBox(Vector2f(70vw, 10vh), L"", Vector2f(15vw, 60vh))),
enter(states.r.fact.getButton(Vector2f(30vw, 15vh), L"Готово", Vector2f(15vw, 75vh))),
back(states.r.fact.getButton({30vw, 15vh}, L"Назад", {55vw, 75vh}))
{}
void States::Editor::EnterPassword::refresh(){
	input.getRect().setString(L"");
	output.setTextFillColor(states.r.colors.outputText);
	enter.setEnable(false);
	enter.getRect().setTextOffset(Vector2f(0, -0.5));
	input.getRect().setStringSizeLimit(states.characterInputLimit);
}
void States::Editor::EnterPassword::check(Event& event){
	input.check(event);
	title.check(event);
	enter.setEnable(!input.getRect().getString().isEmpty());
	output.check(event);
	enter.check(event);
	back.check(event);
	if (input.isClicked()) {
		output.setString(L"");
	}
	if (enter.isClicked()) {
		if (input.getRect().getString() == states.r.mainPassword) {
			states.authorized = true;
			switchState(states.editor.menu);
		}
		else
			output.setString(L"Неверный пароль. Попробуйте ещё раз");
	}
	if (back.isClicked()) {
		states.currentState = &states.mainMenu;
		states.currentState->refresh();
	}
}
void States::Editor::EnterPassword::draw(RenderWindow& window){
	input.draw(window);
	title.draw(window);
	enter.draw(window);
	output.draw(window);
}
void States::Editor::EnterPassword::update(RenderWindow& window, double elTime){
	input.update(window);
	title.draw(window);
	enter.update(window);
	output.draw(window);
	back.update(window);
}

States::Editor::Menu::Menu(States& states) : states(states),
title(states.r.fact.getTextBox({80vw, 15vh}, L"Редактор", {10vw, 5vh})),
_add(states.r.fact.getButton({32.5vw, 20vh}, L"Добавить", {15vw, 40vh})),
_remove(states.r.fact.getButton({32.5vw, 20vh}, L"Удалить", {52.5vw, 40vh})),
_back(states.r.fact.getButton({32.5vw, 20vh}, L"Назад", {15vw + 32.5vw * 0.5f + 2.5vw, 65vh}))
{
}

void States::Editor::Menu::refresh()
{
	
}
void States::Editor::Menu::check(Event& event)
{
	_add.check(event);
	_remove.check(event);
	_back.check(event);
	if (_add.isClicked()) {
		switchState(states.editor.add);
	}
	else if (_remove.isClicked()) {
		states.editor.chooseBlank.setStringButton(L"Удалить");
		switchState(states.editor.chooseBlank);
		states.nextState = &states.confirmation;
	}
	else if (_back.isClicked()) {
		switchState(states.mainMenu);
	}
}
void States::Editor::Menu::draw(RenderWindow& window)
{
	title.draw(window);
	_add.draw(window);
	_remove.draw(window);
	_back.draw(window);
}
void States::Editor::Menu::update(RenderWindow& window, double elTime)
{
	title.draw(window);
	_add.update(window);
	_remove.update(window);
	_back.update(window);
}

States::Editor::Remove::Remove(States& states) : states(states),
title(states.r.fact.getTextBox({70vw, 15vh}, L"Удаление бланка", {15vw, 5vh})),
message(states.r.fact.getTextBox({80vw, 20vh}, L"Удаление прошло успешно", {10vw, 25vh})),
back(states.r.fact.getButton({70vw, 15vh}, L"Назад", {15vw, 80vh}))
{
	
}

States::Editor::RemoveChooseBlank::RemoveChooseBlank(States& states) : States::ChooseBlank(states){

}
void States::Editor::RemoveChooseBlank::check(Event& event) {
	States::ChooseBlank::check(event);
	if (readButton.isClicked()) {
		states.currentState = &states.confirmation;
		states.confirmation.refresh(this, &states.editor.remove);
	}
	if (backButton.isClicked()) {
		switchState(states.editor.menu);
	}
}

States::Editor::Add::Add(States& states) : states(states),
menu(states),
createQustion(states),
blankCreated(states)
{

}

void States::Editor::Add::refresh() {
	newQuestion = Question::Null;
	newQt = Question::Enter;
	switchState(states.editor.add.menu);
}

void States::Editor::Add::Menu::clearData() {
	inputTitle.getRect().setString(L"");
	inputPassword.getRect().setString(L"");
	repeatPassword.getRect().setString(L"");
	states.editor.add.newQuestion = Question::Null;
	states.editor.add.newQt = Question::Enter;
	questionPreview.setString(L"");
}
States::Editor::Add::Menu::Menu(States& states) : states(states),
title(states.r.fact.getTextBox({70vw, 15vh}, L"Создание бланка", {15vw, 5vh})),
inputTitle(states.r.fact.getInputTextBox({37.5vw, 10vh}, L"Введите заголовок", {10vw, 25vh})),
inputPassword(states.r.fact.getInputTextBox({37.5vw, 10vh}, L"Введите пароль", {10vw, 40vh})),
repeatPassword(states.r.fact.getInputTextBox({37.5vw, 10vh}, L"Повторите пароль", {10vw, 55vh})),
addQuestion(states.r.fact.getButton({37.5vw,10vh}, L"Создать вопрос", {52.5vw, 25vh})),
questionPreview(states.r.fact.getTextBox({37.5vw, 25vh}, L"", {52.5vw, 40vh})),
output(states.r.fact.getTextBox({80vw, 10vh}, L"", {10vw, 70vh})),
enter(states.r.fact.getButton({37.5vw, 10vh}, L"Готово", {10vw, 85vh})),
back(states.r.fact.getButton({37.5vw, 10vh}, L"Назад", {52.5vw, 85vh}))
{
	inputTitle.getRect().setStringSizeLimit(states.characterInputLimit);
	inputPassword.getRect().setStringSizeLimit(states.characterInputLimit);
	repeatPassword.getRect().setStringSizeLimit(states.characterInputLimit);
	enter.getRect().setTextOffset({ 0, -0.5 });
	addQuestion.getRect().setCharacterSize(40px);
	questionPreview.setCharacterSize(30px);
}
void States::Editor::Add::Menu::refresh(int)
{
	if (states.editor.add.newQuestion != Question::Null) {
		questionPreview.setString(states.editor.add.newQuestion.question);
	}
	else
		questionPreview.setString(L"");
	output.setString(L"");
	enter.setEnable(false);
}
void States::Editor::Add::Menu::refresh() {
	clearData();
	refresh(0);
}
void States::Editor::Add::Menu::check(Event& event) {
	inputTitle.check(event);
	inputPassword.check(event);
	repeatPassword.check(event);
	addQuestion.check(event);
	enter.check(event);
	back.check(event);
	enter.setEnable(
		inputPassword.getRect().getString() == repeatPassword.getRect().getString() &&
		!(inputTitle.getRect().getString().isEmpty() || inputPassword.getRect().getString().isEmpty())
	); 
	if (enter.isClicked()) {
		states.addBlank(Blank(inputTitle.getRect().getString(), inputPassword.getRect().getString(), 
			states.editor.add.newQuestion, states.editor.add.newQt));
		switchState(states.editor.add.blankCreated);
	}
	if (back.isClicked()) {
		switchState(states.editor.menu);
	}
	if (addQuestion.isClicked()) {
		switchState(states.editor.add.createQustion);
	}
}
void States::Editor::Add::Menu::draw(RenderWindow& window) {
	title.draw(window);
	inputTitle.draw(window);
	inputPassword.draw(window);
	repeatPassword.draw(window);
	addQuestion.draw(window);
	questionPreview.draw(window);
	output.draw(window);
	enter.draw(window);
	back.draw(window);
}
void States::Editor::Add::Menu::update(RenderWindow& window, double elTime) {
	title.draw(window);
	inputTitle.update(window);
	inputPassword.update(window);
	repeatPassword.update(window);
	addQuestion.update(window);
	questionPreview.draw(window);
	output.draw(window);
	enter.update(window);
	back.update(window);
}

States::Editor::Add::CreateQuestion::CreateQuestion(States& states) : states(states),
title(states.r.fact.getTextBox({70vw, 15vh}, L"Создание вопроса", {15vw, 5vh})),
inputQuestion(states.r.fact.getInputTextBox({55vw, 15vh}, L"Введите вопрос", {5vw, 25vh})),
questionType(states.r.fact.getButton({ 30vw, 15vh }, L"", {65vw, 25vh})),
inputRightAnswer(states.r.fact.getInputTextBox({40vw, 15vh}, L"Введите правильный ответ", {5vw, 45vh})),
inputWrongAnswer(states.r.fact.getInputTextBox({40vw, 15vh}, L"Введите неправильный ответ", {5vw, 65vh})),
addRightAnswer(states.r.fact.getButton({20vw, 15vh}, L"Добавить", {50vw, 45vh})),
addWrongAnswer(states.r.fact.getButton({20vw, 15vh}, L"Добавить", {50vw, 65vh})),
removeRightAnswer(states.r.fact.getButton({20vw, 15vh}, L"Удалить", {75vw, 45vh})),
removeWrongAnswer(states.r.fact.getButton({20vw, 15vh}, L"Удалить", {75vw, 65vh})),
enter(states.r.fact.getButton({37.5vw, 10vh}, L"Готово", {10vw, 85vh})),
back(states.r.fact.getButton({37.5vw, 10vh}, L"Назад", {52.5vw, 85vh}))
{
	inputQuestion.getRect().setStringSizeLimit(states.characterInputLimit * 1.5);
	inputRightAnswer.getRect().setStringSizeLimit(states.characterInputLimit);
	inputWrongAnswer.getRect().setStringSizeLimit(states.characterInputLimit);
	addRightAnswer.getRect().setCharacterSize(40px);
	addWrongAnswer.getRect().setCharacterSize(40px);
	removeRightAnswer.getRect().setCharacterSize(40px);
	removeWrongAnswer.getRect().setCharacterSize(40px);
}
void States::Editor::Add::CreateQuestion::clearData()
{
	inputQuestion.getRect().setString(L"");
	inputRightAnswer.getRect().setString(L"");
	inputWrongAnswer.getRect().setString(L"");
	tempQuestion = Question::Null;
	tempQuestionType = Question::Enter;
}
void States::Editor::Add::CreateQuestion::setQuestionType(Question::Type qt)
{
	tempQuestionType = qt;
	switch (qt) {
	case Question::Enter: {
		questionType.getRect().setString(L"Ввод");
	} break;
	case Question::Test: {
		questionType.getRect().setString(L"Тест");
	} break;
	}
}
void States::Editor::Add::CreateQuestion::refresh() {
	clearData();
	addRightAnswer.setEnable(false);
	addWrongAnswer.setEnable(false);
	removeRightAnswer.setEnable(false);
	removeWrongAnswer.setEnable(false);
	inputWrongAnswer.setEnable(false);
	enter.setEnable(false);
	setQuestionType(static_cast<Question::Type>(tempQuestionType));
}
static const int questionTypesCount = 2;
void States::Editor::Add::CreateQuestion::check(Event& event) {
	inputQuestion.check(event);
	questionType.check(event);
	inputRightAnswer.check(event);
	inputWrongAnswer.check(event);
	addRightAnswer.check(event);
	addWrongAnswer.check(event);
	removeRightAnswer.check(event);
	removeWrongAnswer.check(event);
	enter.check(event);
	back.check(event);
	bool isTest = tempQuestionType == Question::Test;

	if (questionType.isClicked()) {
		++tempQuestionType;
		setQuestionType(static_cast<Question::Type>(tempQuestionType %= questionTypesCount));
	}
	addRightAnswer.setEnable(!inputRightAnswer.getRect().getString().isEmpty());
	if (addRightAnswer.isClicked()) {
		tempQuestion.rightAnswers.push_back(inputRightAnswer.getRect().getString());
		inputRightAnswer.getRect().setString(L"");
	}
	removeRightAnswer.setEnable(!tempQuestion.rightAnswers.empty());
	if (removeRightAnswer.isClicked()) {
		tempQuestion.rightAnswers.pop_back();
	}
	addWrongAnswer.setEnable((!inputWrongAnswer.getRect().getString().isEmpty()) && isTest);
	if (addWrongAnswer.isClicked()) {
		tempQuestion.wrongAnswers.push_back(inputWrongAnswer.getRect().getString());
		inputWrongAnswer.getRect().setString(L"");
	}
	removeWrongAnswer.setEnable((!tempQuestion.wrongAnswers.empty()) && isTest);
	if (removeWrongAnswer.isClicked()) {
		tempQuestion.wrongAnswers.pop_back();
	}
	enter.setEnable((!tempQuestion.rightAnswers.empty() && !inputQuestion.getRect().getString().isEmpty()) && (isTest <= (!tempQuestion.wrongAnswers.empty())));
	if (enter.isClicked()) {
		states.editor.add.newQt = static_cast<Question::Type>(tempQuestionType);
		tempQuestion.question = inputQuestion.getRect().getString();
		states.editor.add.newQuestion = tempQuestion;
		states.currentState = &states.editor.add.menu;
		states.editor.add.menu.refresh(0);
	}
	if (back.isClicked()) {
		states.currentState = &states.editor.add.menu;
		clearData();
		states.editor.add.menu.refresh(0);
	}
	isTest = tempQuestionType == Question::Test;
	inputWrongAnswer.setEnable(isTest);
	addRightAnswer.setEnable(!inputRightAnswer.getRect().getString().isEmpty());
	removeRightAnswer.setEnable(!tempQuestion.rightAnswers.empty());
	addWrongAnswer.setEnable((!inputWrongAnswer.getRect().getString().isEmpty()) && isTest);
	removeWrongAnswer.setEnable((!tempQuestion.wrongAnswers.empty()) && isTest);
	enter.setEnable((!tempQuestion.rightAnswers.empty()) && (isTest <= (!tempQuestion.wrongAnswers.empty())));
}
void States::Editor::Add::CreateQuestion::draw(RenderWindow& window) {
	title.draw(window);
	inputQuestion.draw(window);
	questionType.draw(window);
	inputRightAnswer.draw(window);	
	addRightAnswer.draw(window);
	removeRightAnswer.draw(window);
	inputWrongAnswer.draw(window);
	addWrongAnswer.draw(window);
	removeWrongAnswer.draw(window);
	enter.draw(window);
	back.draw(window);
}
void States::Editor::Add::CreateQuestion::update(RenderWindow& window, double elTime) {
	title.draw(window);
	inputQuestion.update(window);
	questionType.update(window);
	inputRightAnswer.update(window);
	addRightAnswer.update(window);
	removeRightAnswer.update(window);
	inputWrongAnswer.update(window);
	addWrongAnswer.update(window);
	removeWrongAnswer.update(window);
	enter.update(window);
	back.update(window);
}

States::Editor::Add::BlankCreated::BlankCreated(States& states) : states(states),
title(states.r.fact.getTextBox({70vw, 15vh}, L"Создание бланка", {15vw, 5vh})),
message(states.r.fact.getTextBox({ 80vw, 20vh }, L"Создание бланка завершено успешно", {10vw, 25vh})),
back(states.r.fact.getButton({70vw, 15vh}, L"Готово", {15vw, 80vh}))
{

}
void States::Editor::Add::BlankCreated::check(Event& event) {
	back.check(event);
	if (back.isClicked()) {
		switchState(states.editor.menu);
	}
}
void States::Editor::Add::BlankCreated::draw(RenderWindow& window) {
	title.draw(window);
	message.draw(window);
	back.draw(window);
}
void States::Editor::Add::BlankCreated::update(RenderWindow& window, double elTime) {
	title.draw(window);
	message.draw(window);
	back.update(window);
}

void States::Editor::Remove::refresh()
{
	if (states.currentBlank) {
		states.deleteBlank(states.currentBlankIndex);
	}
}
void States::Editor::Remove::check(Event& event)
{
	back.check(event);
	if (back.isClicked()) {
		states.currentState = &states.editor.menu;
		states.currentState->refresh();
	}
}
void States::Editor::Remove::draw(RenderWindow& window)
{
	title.draw(window);
	message.draw(window);
	back.draw(window);
}
void States::Editor::Remove::update(RenderWindow& window, double elTime)
{
	title.draw(window);
	message.draw(window);
	back.update(window);
}

States::Editor::Editor(States& states) : states(states),
enterPassword(states),
menu(states),
remove(states),
chooseBlank(states),
add(states)
{}
void States::Editor::refresh() {
	if (!states.authorized) {
		states.currentState = &states.editor.enterPassword;
		states.currentState->refresh();
	}
	else {
		states.currentState = &states.editor.menu;
		states.currentState->refresh();
	}
}
void States::Editor::check(Event& event) {
	
}
void States::Editor::draw(RenderWindow& window) {

}
void States::Editor::update(RenderWindow& window, double elTime) {

}
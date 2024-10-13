#pragma once
#include "StatesHeader.h"
#define switchState(state) {states.currentState = &state; states.currentState->refresh();}
class States
{
private:
	void deleteBlank(int index);
	void addBlank(const Blank& blank);
	class MainMenu : public State {
	private:
		States& states;
		TextBox& title;
		TButton& startButton, &editorButton;
	public:
		MainMenu(States& states);
		void check(Event& event) override;
		void draw(RenderWindow& window) override;
		void update(RenderWindow& window, double elTime) override;
	};
	class ChooseBlank : public State {
	protected:
		States& states;
		TextBox& title;
		vector<std::reference_wrapper<TButton>> blankButtons;
		RectangleShape border;
		TButton& backButton, &readButton;
		void setBlanksPosition(const Vector2f& pos);
		FloatRect getBlanksGlobalBounds() const;
		const Vector2f 
			defaultPosition = Vector2f(15vw, 30vh),
			blankListRectSize = Vector2f(70vw, 45vh);
		Vector2f pos;
		bool mouseInRect;
	public:
		ChooseBlank(States& states);
		void setStringButton(const sf::String& str);
		const sf::String& getStringButton() const;
		void refresh() override;
		virtual void check(Event& event) override;
		void draw(RenderWindow& window) override;
		void update(RenderWindow& window, double elTime) override;
		friend void States::deleteBlank(int);
		friend void States::addBlank(const Blank& blank);
	};
	class EnterPassword : public State {
	private:
		States& states;
		TextBox& title;
		BiTextBox& input;
		TextBox& output;
		TButton& enterButton, & answerQuestionButton, & backButton;
		TextBox& timer;
	public:
		EnterPassword(States& states);
		void refresh();
		void check(Event& event);
		void draw(RenderWindow& window);
		void update(RenderWindow& window, double elTime);
	};
	class AnswerQuestion : public State {
	private:
		States& states;
		// Enter
		int attempts = 3;
		BiTextBox& input;
		TButton& enter;
		TButton& back;
		//
		TextBox& output;
		TextBox& title, &question;
		// Test
		vector<std::reference_wrapper<TButton>> buttons;
		TButton& back1;
		bool failed;
		//
	public:
		AnswerQuestion(States& states);
		void refresh();
		void check(Event& event);
		void draw(RenderWindow& window);
		void update(RenderWindow& window, double elTime);
	};
	class PasswordBlank : public State {
	private:
		States& states;
		TextBox& title, &bTitle, &bPassword;
		TButton
			& showPasswordButton,
			& copyButton,
			& backButton;
		bool showPassword;
	public:
		PasswordBlank(States& states);
		void refresh();
		void check(Event& event);
		void draw(RenderWindow& window);
		void update(RenderWindow& window, double elTime);
	};
	class Intro : public State {
	private:
		States& states;
		class Welcome : public State {
		private:
			States& states;
			TextBox& title, &welcome;
			TButton& next;
		public:
			Welcome(States& states);
			void check(Event& event) override;
			void draw(RenderWindow& window) override;
			void update(RenderWindow& window, double elTime) override;
		};
		class About : public State {
		private:
			States& states;
			TextBox& title, &info;
			TButton& next;
		public:
			About(States& states);
			void check(Event& event) override;
			void draw(RenderWindow& window) override;
			void update(RenderWindow& window, double elTime) override;
		};
		class CreatePassword : public State {
		private:
			States& states;
			TextBox& title;
			BiTextBox& writePassword, & repeatPassword;
			TButton& enter;
		public:
			CreatePassword(States& states);
			void refresh() override;
			void check(Event& event) override;
			void draw(RenderWindow& window) override;
			void update(RenderWindow& window, double elTime) override;
		};
		Welcome welcome;
		About about;
		CreatePassword createPassword;
	public:
		Intro(States& states);
		void refresh() override;
	};
	class Confirmation : public State {
	private:
		States& states;
		TextBox& title, &message;
		TButton& yes, &no;
		bool _confirmed;
		State* backState, *nextState;
		unique_ptr<RectangleShape> additiveBg;
	public:
		Confirmation(States& states);
		void refresh();
		void refresh(State* backState, State* nextState, const String& message = L"Вы уверены в этом?");
		void check(Event& event);
		void draw(RenderWindow& window);
		void update(RenderWindow& window, double elTime);
		bool confirmed();
	};
	class Editor : public State {
	private:
		States& states;
		class EnterPassword : public State {
		private:
			States& states;
			TextBox& title, & output;
			BiTextBox& input;
			TButton& enter, & back;
		public:
			EnterPassword(States& states);
			void refresh();
			void check(Event& event);
			void draw(RenderWindow& window);
			void update(RenderWindow& window, double elTime);
		};
		class Menu : public State {
		private:
			States& states;
			TextBox& title;
			TButton& _add, & _remove, & _back;
		public:
			Menu(States& states);
			void refresh();
			void check(Event& event);
			void draw(RenderWindow& window);
			void update(RenderWindow& window, double elTime);
		};
		class Add : public State {
		private:
			States& states;
			Question newQuestion = Question::Null;
			Question::Type newQt = Question::Enter;
			class Menu : public State {
			private:
				States& states;
				TextBox& title, & output, & questionPreview;
				BiTextBox& inputPassword, & repeatPassword, & inputTitle;
				TButton& enter, & back, & addQuestion;
				void clearData();
			public:
				Menu(States& states);
				void refresh();
				void refresh(int);
				void check(Event& event);
				void draw(RenderWindow& window);
				void update(RenderWindow& window, double elTime);
			};
			class CreateQuestion : public State {
			private:
				States& states;
				Question tempQuestion = Question::Null;
				int tempQuestionType = Question::Enter;
				TextBox& title;
				BiTextBox& inputRightAnswer, & inputWrongAnswer, &inputQuestion;
				TButton& enter, & back, & addRightAnswer, & addWrongAnswer, & questionType,
					& removeRightAnswer, & removeWrongAnswer;
				void setQuestionType(Question::Type qt);
				void clearData();
			public:
				CreateQuestion(States& states);
				void refresh();
				void check(Event& event);
				void draw(RenderWindow& window);
				void update(RenderWindow& window, double elTime);
			};
			class BlankCreated : public State {
			private:
				States& states;
				TextBox& title, &message;
				TButton& back;
			public:
				BlankCreated(States& states);
				void check(Event& event);
				void draw(RenderWindow& window);
				void update(RenderWindow& window, double elTime);
			};
			Menu menu;
			CreateQuestion createQustion;
			BlankCreated blankCreated;
		public:
			Add(States& states);
			void refresh();
		};
		class RemoveChooseBlank : public States::ChooseBlank {
		public:
			RemoveChooseBlank(States& states);
			void check(Event& event) override;
			friend void States::deleteBlank(int);
			friend void States::addBlank(const Blank& blank);
		};
		class Remove : public State {
		private:
			States& states;
			TextBox& title, &message;
			TButton& back;
		public:
			Remove(States& states);
			void refresh();
			void check(Event& event);
			void draw(RenderWindow& window);
			void update(RenderWindow& window, double elTime);
		};
		EnterPassword enterPassword;
		Menu menu;
		RemoveChooseBlank chooseBlank;
		Remove remove;
		Add add;
	public:
		Editor(States& states);
		void refresh();
		void check(Event& event);
		void draw(RenderWindow& window);
		void update(RenderWindow& window, double elTime);
		friend class States;
	};
	static const int characterInputLimit = 50;
	Resource& r;
	bool authorized;
	int currentBlankIndex;
	Blank* currentBlank;
	State* nextState;
	Intro intro;
	MainMenu mainMenu;
	ChooseBlank chooseBlank;
	EnterPassword enterPassword;
	AnswerQuestion answerQuestion;
	PasswordBlank passwordBlank;
	Confirmation confirmation;
	Editor editor;
public:
	State* currentState;
	States(Resource& r);
	void check(Event& event);
	void draw(RenderWindow& window);
	void update(RenderWindow& window, double elTime);
};


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixed = 5 };

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	int Answers = 0;
	enQuestionsLevel QuLevel;
	enOperationType OpType;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	int NumberOfQuestion = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
	int Number;

	do
	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> Number;

	} while (Number < 1 || Number > 100);

	return Number;
}

enQuestionsLevel ReadQuestionsLevel()
{
	int Question;

	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> Question;

	} while (Question < 1 || Question > 4);

	return (enQuestionsLevel)Question;
}

enOperationType ReadOperationType()
{
	int Operation;

	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> Operation;

	} while (Operation < 1 || Operation > 5);

	return (enOperationType)Operation;
}

int SimpleCalculator(int Number1, int Number2, enOperationType Operation)
{
	switch (Operation)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	}
	return 0;
}

enOperationType GetRandomOperation()
{
	return (enOperationType)RandomNumber(1, 4);
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OperationType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::Mixed)
	{
		OperationType = GetRandomOperation();
	}

	Question.OpType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.Answers = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.Answers = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.Answers = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
		Question.QuLevel = QuestionLevel;
		return Question;
	}

	return Question;
}

void GenerateQuizzQuestion(stQuizz& Quizz)
{
	for (int Question = 0; Question < Quizz.NumberOfQuestion; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
	}
}

string QuestionsName(enQuestionsLevel Questions)
{
	string arrQuestion[4] = { "Easy", "Med", "Hard", "Mix" };
	return arrQuestion[Questions - 1];
}

string OperationName(enOperationType Operation)
{
	string arrOperation[5] = { "+","-","*","/","Mix" };
	return arrOperation[Operation - 1];
}

void SetQuizzColor(bool IsRight)
{
	system(IsRight ? "color 2F" : "color 4F");

	if (!IsRight)
		cout << '\a';
}

void PrintTheQuestion(stQuizz& Quizz, short NumberQuestion)
{
	cout << "\nQuestion [" << NumberQuestion + 1
		<< "/" << Quizz.NumberOfQuestion << "]\n\n";
	cout << Quizz.QuestionList[NumberQuestion].Number1 << " "
		<< OperationName(Quizz.QuestionList[NumberQuestion].OpType) << " "
		<< Quizz.QuestionList[NumberQuestion].Number2 << " = ";
	cout << "\n__________________\n";
}

void CountQuizzQuestion(stQuizz& Quizz, int Number, int RightAnswer)
{
	if (Number == RightAnswer)
		Quizz.NumberOfRightAnswers++;
	else
		Quizz.NumberOfWrongAnswers++;
}

void ReadQuestionAnswers(stQuizz& Quizz, int RightAnswers)
{
	int Number;
	cin >> Number;

	if (Number == RightAnswers)
	{
		cout << "\nRight Answer :-) \n";
		SetQuizzColor(true);
	}
	else
	{
		cout << "\nWrong Answer :(- ";
		cout << "\nThe Right Answer is : " << RightAnswers << endl;
		SetQuizzColor(false);
	}

	CountQuizzQuestion(Quizz, Number, RightAnswers);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		ReadQuestionAnswers(Quizz, Quizz.QuestionList[QuestionNumber].Answers);
	}
}

string Tabs(int Number)
{
	string T = "";

	for (int i = 1; i <= Number; i++)
	{
		T += "\t";
	}

	return T;
}

string GetFinalResultText(stQuizz Quizz)
{
	if (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers)
	{
		SetQuizzColor(true);
		return "PASS :-) ";
	}
	else
	{
		SetQuizzColor(false);
		return "FAIL :)- ";
	}
}

void ShowGameOverScreen()
{
	cout << endl << Tabs(5) << "______________________________________\n";
	cout << endl << Tabs(6) << " +++GAME OVER+++ \n";
	cout << endl << Tabs(5) << "______________________________________\n";
}

void ShowFinalResultsScreen(stQuizz Quizz)
{
	ShowGameOverScreen();
	cout << endl << Tabs(5) << "______________________________________\n";
	cout << endl << Tabs(5) << "Final Results is " << GetFinalResultText(Quizz);
	cout << endl << Tabs(5) << "______________________________________\n\n";
}

void PrintQuizzResults(stQuizz Quizz)
{
	ShowFinalResultsScreen(Quizz);
	cout << Tabs(5) << "Number of Question: " << Quizz.NumberOfQuestion << endl;
	cout << Tabs(5) << "Questions Level   : " << QuestionsName(Quizz.QuestionLevel) << endl;
	cout << Tabs(5) << "Operations Type   : " << OperationName(Quizz.OperationType) << endl;
	cout << Tabs(5) << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << Tabs(5) << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << Tabs(5) << "______________________________________\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestion = ReadHowManyQuestions();
	Quizz.QuestionLevel = ReadQuestionsLevel();
	Quizz.OperationType = ReadOperationType();

	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'y';

	do
	{
		ResetScreen();
	    PlayMathGame();

		cout << endl << Tabs(5) << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

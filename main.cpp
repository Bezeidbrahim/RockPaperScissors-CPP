#include <iostream>
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.
using namespace std;

enum enGameChoice{ Stone = 1, Paper=2 , Scissors=3};
enum enWinner { PlayerWins=1, ComputerWins=2, Draw=3 };

struct stRound {
	int roundNoumber = 0;
	enGameChoice playerChoice;
	enGameChoice computerChoice;
	enWinner Winner;
	string WinnerName="";
};

struct stGameResult {
	short GemeRounds = 0;
	short PlayerWins = 0;
	short ComputerWins = 0;
	short Draws = 0;
	enWinner GameWinner;
	string WinnerName="";

};

int RandomNumber(int From, int To) {

	return rand() % (To - From + 1) + From;
}


short ReadHowManyRound() {
	
	short round = 1;
	do{
	cout << "How Many Rounds 1 to 10 ? : ";
	cin >> round;
	} while (round < 1 || round > 10);
	return round;
}

enGameChoice ReadPlayerChoice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}


enGameChoice GetComputerChoice() {
	return (enGameChoice)RandomNumber(1,3);
}

enWinner DecideWinner(stRound Round) {
	if (Round.playerChoice== Round.computerChoice) {
		return enWinner::Draw;
	}
	else if ((Round.playerChoice == Stone && Round.computerChoice == Scissors) || (Round.playerChoice == Paper && Round.computerChoice == Stone) || (Round.playerChoice == Scissors && Round.computerChoice == Paper)) {
		return enWinner::PlayerWins;
	}
	else {
		return enWinner::ComputerWins;
	}
}

string ChoiceName(enGameChoice choice) {
	string arrGameChoice[3] = { "Stone", "Paper", "Scissors" };
	return arrGameChoice[choice - 1];
}

string WinnerName(enWinner choice) {
	string arrWinnerName[3]= { "Player1", "Computer", "No Winner (Draw)" };
	return arrWinnerName[choice - 1];
}

void PrintRoundResult(stRound Round) {
	cout << "\n------------ Round [" << Round.roundNoumber << "] ------------\n";
	cout << "Player Choice   : " << ChoiceName(Round.playerChoice) << endl;
	cout << "Computer Choice : " << ChoiceName(Round.computerChoice) << endl;
	cout << "Round Winner    : [" << Round.WinnerName << "]" << endl;
	cout << "---------------------------------------------------------" << endl;
}
enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes) {

	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::PlayerWins;
	else if (PlayerWinTimes < ComputerWinTimes)
		return enWinner::ComputerWins;
	else
		return enWinner::Draw;
}
stGameResult FillGameResult(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {
	stGameResult GameResult;

	GameResult.GemeRounds = GameRounds;
	GameResult.PlayerWins = PlayerWinTimes;
	GameResult.ComputerWins = ComputerWinTimes;
	GameResult.Draws = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(GameResult.PlayerWins, GameResult.ComputerWins);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

string Tab(short NumberOfTab) {
	string t = "";
	for (int i = 0; i < NumberOfTab; i++) {
		t += "\t";
	}
	return t;

}
void ShowGameOverScren() {

	cout << Tab(2) << "----------------------------------------------------------\n\n";
	cout << Tab(2) << "              +++ G a m e O v e r +++\n";
	cout << Tab(2) << "----------------------------------------------------------\n\n";

}

void SetWinnerScreenColor(enWinner Winner) {

	switch (Winner) {
	case enWinner::PlayerWins:
		system("color 2F");
		break;
	case enWinner::ComputerWins:
		system("color 4F");
		break;
	default:
		system("color 6F");
		break;

	}

}

void ShowFinalGameResult(stGameResult GameResult) {
	cout << Tab(2) << "_____________________[Game Result]________________________\n\n";
	cout << Tab(2) << "Game Rounds        : " << GameResult.GemeRounds << endl;
	cout << Tab(2) << "Player won Times   : " << GameResult.PlayerWins << endl;
	cout << Tab(2) << "Computer won Times : " << GameResult.ComputerWins << endl;
	cout << Tab(2) << "Draw Times         : " << GameResult.Draws << endl;
	cout << Tab(2) << "Final Winner       : " << GameResult.WinnerName << endl;
	cout << Tab(2) << "___________________________________________________________\n\n";

	SetWinnerScreenColor(GameResult.GameWinner);
}

stGameResult PlayGame(short HowManyRounds) {

	stRound Round;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
		cout << "\nRound [" << GameRound << "] begins:\n";
		Round.roundNoumber = GameRound;
		Round.playerChoice = ReadPlayerChoice();
		Round.computerChoice = GetComputerChoice();
		Round.Winner = DecideWinner(Round);
		Round.WinnerName = WinnerName(Round.Winner);

		if (Round.Winner == enWinner::PlayerWins)
			PlayerWinTimes++;
		else if (Round.Winner == enWinner::ComputerWins)
			ComputerWinTimes++;
		else
			DrawTimes++;

		SetWinnerScreenColor(Round.Winner);

		PrintRoundResult(Round);
	}

	return FillGameResult(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}

void ResetScreen() {
	system("cls");
	system("color 0F");
}
void StartGame() {

	char PlayAgain = 'Y';
	do {

		ResetScreen();
		stGameResult GameResult = PlayGame(ReadHowManyRound());
		ShowGameOverScren();
		ShowFinalGameResult(GameResult);

		cout << endl << Tab(3) << "\nDo you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main() {

	srand((unsigned)time(NULL));
	StartGame();
	
	return 0;
}








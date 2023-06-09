#include<iostream>
#include <ctime>
#include <fstream>
#include <string>
#include<conio.h>
#include <cstdlib>
#include <cmath>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <cwchar>
/*This game can be played with any numbers of tokens and players*/
using namespace std;
int indexes[4][4] = { {0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15} };//indexes of tokens on board
int startingPoint[4] = { 17,30,56,43 };//starting point of each code
int addition[3] = { 22,32,27 };//array used in MakingPathToHome
bool checking = false;//checking of adding in score twice when token is killed
bool anotherchecking = false;//checking of adding in score twice when token is reached
bool TokenOutCheck = false;//for checking and taking the token out when the token is killed at starting point
bool isWon = false;//To check if any player has won and then to break both loops in MainGameplay
bool ruleoption = false;//for appropriate Continue Option for Rules Menu
char TokenOutchoice;
struct LUDO {
	short int NoOfPlayers;//Number of Players playing the Game
	char tokens[4][4];//tokens names
	char names[4][20];//names of player
	char tokensavailable[4][4];//tokens that are available to start game with
	char tokenreached[4][4];//tokens that have reached home
	char board[88];//LUDO bord
	short int scores[4][4];//scores of tokens
	char TokenOut[4][4];//tokens that are available on board
	char starting;//To get the PLayer from which game should be started
	short int noOfTokens;//Number of Tokens Used in Playing Game
};
void TurnDisplay(int player, LUDO& l);// To display player's turn
void StartScreen();//To Display starting screen
void SavedGamesDisplay(LUDO& l);//to display all the saved games
void CorrectPosition(int player, int index, int dice, LUDO& l);//to move the token to right path
int TokensOut(int player, LUDO& l);//Numbers of Tokens on the board
void displayboard(LUDO& l);//Displaying The Board
void TokenReached(int player, int index, LUDO& l);//Number of Tokens that have reached final position
void intitarray(LUDO& l);//initiating board and other members of LUDO Struct
void inputNames(LUDO& l);//Input names accorfing to number of player
void killToken(int playerindex, int player, int position, LUDO& l, int dice);//killing the token
bool isTokenAvailable(int player, char choice, LUDO& l);//checking if the token available for taking out
void TakeTokenOut(int player, LUDO& l);//taking the token out when die number is 6
void movetoken(int player, LUDO& l, int dice);//For moving the token
void MainGameplay(LUDO& l);//from where the functions are called
void NewGame();//for playing new game
void SavingGame(LUDO l);//for saving game on user choice
void OpenSaveGame();//for opening the saved games
void Rules();//for displaying rules of games
void About();//About the author of code
void Menu();//Menu for selecting out of various choices
void ClearingAndDisplaying(int player, LUDO& l) {
	system("CLS");
	TurnDisplay(player, l);
	displayboard(l);
}
//Main Function
int main() {
	srand((time(0)));
	ShowWindow(GetConsoleWindow(), 3);//opening console in full screen
	StartScreen();
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);//changing font size
	Menu();
	system("pause");
}
int TokensAvailable(int player, LUDO& l) {
	int count = 0;
	for (int i = 0; i < l.noOfTokens; i++)
		if (l.tokensavailable[player][i] != ' ')
			count++;
	return count;
}
int TokensOut(int player, LUDO& l) {//to check if there are more than one token out on the board
	int count = 0;
	for (int i = 0; i < l.noOfTokens; i++)
		if (l.TokenOut[player][i] != ' ')
			count++;
	return count;
}
void displayboard(LUDO& l) {
	cout << "\t\t\t _________________________________________________________________\n";
	cout << "\t\t\t|           |           |__" << l.board[27] << "__|__" << l.board[28] << "__|__" << l.board[29] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.board[0] << "     |     " << l.board[1] << "     |__" << l.board[26] << "__|__" << l.board[73] << "__|__" << l.board[30] << "__|     " << l.board[4] << "     |     " << l.board[5] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.board[25] << "__|__" << l.board[74] << "__|__" << l.board[31] << "__|___________|___________|\n";
	cout << "\t\t\t|           |           |__" << l.board[24] << "__|__" << l.board[75] << "__|__" << l.board[32] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.board[2] << "     |     " << l.board[3] << "     |__" << l.board[23] << "__|__" << l.board[76] << "__|__" << l.board[33] << "__|     " << l.board[6] << "     |     " << l.board[7] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.board[22] << "__|__" << l.board[77] << "__|__" << l.board[34] << "__|___________|___________|\n";
	cout << "\t\t\t|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t| " << l.board[16] << " | " << l.board[17] << " | " << l.board[18] << " | " << l.board[19] << " | " << l.board[20] << " | " << l.board[21] << " |                 | " << l.board[35] << " | " << l.board[36] << " | " << l.board[37] << " | " << l.board[38] << " | " << l.board[39] << " | " << l.board[40] << " |\n";
	cout << "\t\t\t|___|___|___|___|___|___|                 |___|___|___|___|___|___|\n";
	cout << "\t\t\t|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t| " << l.board[67] << " | " << l.board[68] << " | " << l.board[69] << " | " << l.board[70] << " | " << l.board[71] << " | " << l.board[72] << " |     L U D O     | " << l.board[82] << " | " << l.board[81] << " | " << l.board[80] << " | " << l.board[79] << " | " << l.board[78] << " | " << l.board[41] << " |\n";
	cout << "\t\t\t|___|___|___|___|___|___|                 |___|___|___|___|___|___|\n";
	cout << "\t\t\t|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t| " << l.board[66] << " | " << l.board[65] << " | " << l.board[64] << " | " << l.board[63] << " | " << l.board[62] << " | " << l.board[61] << " |                 | " << l.board[47] << " | " << l.board[46] << " | " << l.board[45] << " | " << l.board[44] << " | " << l.board[43] << " | " << l.board[42] << " |\n";
	cout << "\t\t\t|___|___|___|___|___|___|_________________|___|___|___|___|___|___|\n";
	cout << "\t\t\t|           |           |__" << l.board[60] << "__|__" << l.board[87] << "__|__" << l.board[48] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.board[8] << "     |     " << l.board[9] << "     |__" << l.board[59] << "__|__" << l.board[86] << "__|__" << l.board[49] << "__|     " << l.board[12] << "     |     " << l.board[13] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.board[58] << "__|__" << l.board[85] << "__|__" << l.board[50] << "__|___________|___________|\n";
	cout << "\t\t\t|           |           |__" << l.board[57] << "__|__" << l.board[84] << "__|__" << l.board[51] << "__|           |           |\n";
	cout << "\t\t\t|     " << l.board[10] << "     |     " << l.board[11] << "     |__" << l.board[56] << "__|__" << l.board[83] << "__|__" << l.board[52] << "__|     " << l.board[14] << "     |     " << l.board[15] << "     |\n";
	cout << "\t\t\t|___________|___________|__" << l.board[55] << "__|__" << l.board[54] << "__|__" << l.board[53] << "__|___________|___________|\n";
}
void intitarray(LUDO& l) {
	l.starting = 0;
	for (int i = 0; i < 88; i++)
		l.board[i] = ' ';
	char token = 'a';
	for (int i = 0; i < l.NoOfPlayers; i++) {
		for (int j = 0; j < l.noOfTokens; j++) {
			l.TokenOut[i][j] = ' ';
			l.tokenreached[i][j] = ' ';
			l.scores[i][j] = 0;
			l.board[i * 4 + j] = token;//initializing Board's Element
			l.tokens[i][j] = token;//token's array filling
			l.tokensavailable[i][j] = token++;//available Token's array initializing
		}
	}
}
void inputNames(LUDO& l) {//inputing the names of players
	for (int i = 0; i < l.NoOfPlayers; i++) {
		cout << "Enter Name of Player " << i + 1 << " : ";
		cin >> l.names[i];
	}
}
int ReachedCount(int player, LUDO& l) {
	int count = 0;
	for (int i = 0; i < l.noOfTokens; i++)
		count = l.tokenreached[player][i] != ' ' ? count + 1 : count;
	return count;
}
void TokenReached(int player, int index, LUDO& l) {
	short int previous = startingPoint[player] + l.scores[player][index];
	if (player != 0) {
		previous = previous > 67 ? previous %= 52 : previous;
		previous = l.scores[player][index] >= 51 ? l.scores[player][index] + addition[player - 1] : previous;
	}
	l.tokenreached[player][index] = l.tokens[player][index];
	l.TokenOut[player][index] = ' ';
	l.tokensavailable[player][index] = ' ';
	l.board[previous] = ' ';
	if (ReachedCount(player, l) == l.noOfTokens) {
		system("CLS");
		cout << "\n\n\n\n\t\t\t";
		cout << l.names[player] << " has Won!!!";
		isWon = true;
		return;
	}
	short int dice = rand() % 6 + 1;
	ClearingAndDisplaying(player, l);
	cout << "Bonus Turn on reaching The Token: \n";
	cout << "Die Number : " << dice << endl;
	if (dice != 6 and !TokensOut(player, l))
		return;
	else if (dice == 6 and !TokensOut(player, l))
		TakeTokenOut(player, l);
	else if (TokensOut(player, l))
		movetoken(player, l, dice);
}
void killToken(int playerindex, int player, int position, LUDO& l, int dice) {
	short int fundice;
	if (l.board[position] != ' ') {
		int i, j, funplayer/*player whose token is killed*/, index;
		for (i = 0; i < 4; i++)
			for (j = 0; j < l.noOfTokens; j++)
				if (l.tokens[i][j] == l.board[position]) {
					funplayer = i;
					index = j;
					break;
				}
		if (position == startingPoint[funplayer]) {
			cout << (funplayer == player ? "You can't bring out the token When there is already a token present\n" : "You can't Kill the player at it's starting point\n");
			if (TokensOut(player, l) >= 2) {
				cout << "Choose Another Token\n"; movetoken(player, l, dice);
				checking = true;
			}
			else {
				checking = true; return;
			}
		}
		else if (funplayer == player) {
			cout << "You can't kill your own player\n";
			if (TokensOut(player, l) >= 2) {
				cout << "Choose Another Token\n"; movetoken(player, l, dice);
				checking = true;
			}
			else return;
		}
		else {
			l.board[indexes[funplayer][index]] = l.board[position];
			l.board[position] = ' ';
			l.tokensavailable[funplayer][index] = l.tokens[funplayer][index];//making it available
			l.TokenOut[funplayer][index] = ' ';
			l.scores[funplayer][index] = 0;
			if (position == startingPoint[player]) {
				TokenOutCheck = true;
				TakeTokenOut(player, l);
				checking = true;
			}
			fundice = rand() % 6 + 1;
			if (fundice != 6 and !TokensOut(player, l))
				return;
			else if (fundice == 6 and !TokensOut(player, l))
				TakeTokenOut(player, l);
			else if (TokensOut(player, l)) {
				CorrectPosition(player, playerindex, dice, l);
				ClearingAndDisplaying(player, l);
				cout << "Bonus Turn on Killing The Token\n";
				cout << "Die Number is " << fundice << endl;
				movetoken(player, l, fundice);
				checking = true;
			}
		}
	}
}
bool isTokenAvailable(int player, char choice, LUDO& l) {//checking wheather the selected token is present
	for (int i = 0; i < l.noOfTokens; i++)
		if (l.tokensavailable[player][i] == choice)
			return true;
	return false;
}
void TakeTokenOut(int player, LUDO& l) {//taking the token out when, no any token is out on board
	if (ReachedCount(player, l) == 4 or TokensOut(player, l) == l.noOfTokens) return;
	 short int index;
	if (!TokenOutCheck) {
		cout << "Choose The Token You Want to Bring Out : ";
		for (int i = 0; i < l.noOfTokens; i++) {
			if (l.tokensavailable[player][i] != ' ')
				cout << l.tokensavailable[player][i] << ' ';
		}cout << ": ";
		do {//making the right choice
			cin >> TokenOutchoice;
			if ((!isTokenAvailable(player, TokenOutchoice, l)))
				cout << "Invalid Choice! Choose Only Available Token : ";
		} while (!isTokenAvailable(player, TokenOutchoice, l));
		TokenOutCheck = true;
	}
		for (int i = 0; i < l.noOfTokens; i++)
			if (l.tokens[player][i] == TokenOutchoice)
				index = i;//the index where the choosen token is present
	short int start = startingPoint[player];
	if (l.board[start] != ' ') {
		killToken(index, player, start, l, 6);
		checking = false;
		TokenOutCheck = false;
	}
	if (TokenOutCheck) {
		l.board[start] = l.board[indexes[player][index]];//taking the token out
		l.board[indexes[player][index]] = ' ';//replacing the token with space on the home
		l.tokensavailable[player][index] = ' ';//making it unavilaible for coming on to the board
		l.TokenOut[player][index] = TokenOutchoice;
		TokenOutCheck = false;
		short int dice = rand() % 6 + 1;
		ClearingAndDisplaying(player, l);
		cout << "Bonus Turn on Taking The Token Out\nDie Number : " << dice << endl;
		movetoken(player, l, dice);
	}
}
void MakingPathToHome(int player, int index, int dice, LUDO& l, int previous) {
	if (l.scores[player][index] >= 51)
		previous = l.scores[player][index] + addition[player - 1];
	l.board[l.scores[player][index] + dice + addition[player - 1]] = l.board[previous];
	l.board[previous] = ' ';
	l.scores[player][index] += dice;
}
void CorrectPosition(int player, int index, int dice, LUDO& l) {
	short int position;
	short int start = startingPoint[player];
	short int previous = start + l.scores[player][index];
	if (player >= 1) {
		if (previous > 67)
			previous %= 52;
		if (previous >= 0 and previous <= 10)
			previous += 52;
		if (l.scores[player][index] + dice > 50) {
			MakingPathToHome(player, index, dice, l, previous);
			return;
		}
		if (previous == 67) {
			position = 15 + dice;
			killToken(index, player, position, l, dice);
			if (checking or anotherchecking) { checking = false; anotherchecking = false; return; }
			l.board[position] = l.board[previous];
		}
		else if ((start + l.scores[player][index] + dice > 67)) {
			position = (start + l.scores[player][index] + dice) % 52;
			if (position >= 0 and position <= 10)
				position += 52;
			killToken(index, player, position, l, dice);
			if (checking or anotherchecking) { checking = false; anotherchecking = false; return; }
			l.board[position] = l.board[previous];
		}
		else {
			position = start + l.scores[player][index] + dice;
			killToken(index, player, position, l, dice);
			if (checking or anotherchecking) { checking = false; anotherchecking = false; return; }
			l.board[position] = l.board[previous];
		}
		l.board[previous] = ' ';
	}
	else {
		position = start + l.scores[player][index] + dice;
		killToken(index, player, position, l, dice);
		if (checking or anotherchecking) { checking = false; anotherchecking = false; return; }
		l.board[position] = l.board[previous];
		l.board[previous] = ' ';
	}
	l.scores[player][index] += dice;
}

void movetoken(int player, LUDO& l, int dice) {
	char choiceToken = 'u';
	bool move = true;
	if (dice == 6 and TokensAvailable(player, l)) {
		move = false;
		cout << "Do you Want to bring another token Out? \nPress y for Yes and n for No ";
		do {
			choiceToken = _getch();
			cout << endl;
			if (choiceToken != 'y' and choiceToken != 'n')
				cout << "Invalid Choice! Choose Only y or n : ";
		} while (choiceToken != 'y' and choiceToken != 'n');
	}
	if (choiceToken == 'y')
		TakeTokenOut(player, l);
	else if (choiceToken == 'n' or move) {
		char choice; short int index;
		cout << "Which Token Do you want to move : ";
		do {
			index = -1;
			cin >> choice;
			for (int i = 0; i < l.noOfTokens; i++)
				if (l.tokens[player][i] == choice)
					index = i;//the index where the choosen token is present
			if (index == -1 or l.TokenOut[player][index] != choice)
				cout << "Token is not available! Enter Right choice : ";
		} while (index == -1 or l.TokenOut[player][index] != choice);
		//moving token
		if (l.scores[player][index] + dice == 56) {
			cout << "Token Reached" << endl;
			TokenReached(player, index, l);
			return;
		}
		else if (l.scores[player][index] + dice > 55) {
			cout << "You can't move forward\n";
			if (TokensOut(player, l) == 2 or TokensOut(player, l) == 3) {
				cout << "Choose Another Token\n"; movetoken(player, l, dice);
				anotherchecking = true;
			}
			else return;
		}
		CorrectPosition(player, index, dice, l);
		if (dice == 6) {
			dice = rand() % 6 + 1;
			ClearingAndDisplaying(player, l);
			cout << "Bonus Turn on Getting a SIX\n";
			cout << "Die Number : " << dice << endl;
			movetoken(player, l, dice);
		}
	}
}
void TurnDisplay(int player, LUDO& l) {
	string name = l.names[player];
	short int length = name.length() + 11;
	cout << "\t\t\t\t\t\t ";
	for (int i = 0; i < length; i++)
		cout << '_'; cout << endl;
	cout << "\t\t\t\t\t\t|  " << name << "'s Turn  |\n";
	cout << "\t\t\t\t\t\t|";
	for (int i = 0; i < length; i++)
		cout << '_'; cout << "|\n";
}
void MainGameplay(LUDO& l) {
	char getch;
	int dice = 0;
	int i = l.starting;
	while (true)
	{
		for (; i < l.NoOfPlayers; i++) {
			system("CLS");
			TurnDisplay(i, l);
			displayboard(l);
			cout << "Press any key to roll the die or \'S\' to Save Game ";
			getch = _getch();
			if (getch == 'S') {
				SavingGame(l);
				Menu();
			}
			dice = rand() % 6 + 1;
			cout << "\n" << "Die Number :" << dice << endl;
			if ((dice != 6 and !TokensOut(i, l)))
				continue;
			if (dice == 6 and !TokensOut(i, l))//taking the token out
				TakeTokenOut(i, l);
			else if (TokensOut(i, l))
				movetoken(i, l, dice);
			if (isWon)
				break;
		}
		if (isWon) {
			isWon = false;
			break;
		}
		i = 0;
	}
	cout << "\n\n\nPress any key to go back to Main Menu ";
	_getch();
	Menu();
}
void NewGame() {
	LUDO l;
	system("CLS");
	cout << "Enter Number of Tokens <1-4> : ";
	do {
		cin >> l.noOfTokens;
		if (l.noOfTokens <= 0 or l.noOfTokens > 4)
			cout << "There Must be at least 1 Token to play with ";
	} while (l.noOfTokens <= 0 or l.noOfTokens > 4);
	cout << "Enter Number of Players <2-4> : ";
	do {
		cin >> l.NoOfPlayers;
		if (l.NoOfPlayers <= 1 or l.NoOfPlayers > 4)
			cout << "There must be at least 2-4 players ";
	} while (l.NoOfPlayers <= 1 or l.NoOfPlayers > 4);
	intitarray(l);
	inputNames(l);
	ruleoption = true;
	Rules();
	system("CLS");
	MainGameplay(l);
}
void SavingGame(LUDO l) {
	ofstream save("SavedGames.ludo", ios::app | ios::binary);
	save.write((char*)& l, sizeof(l));
	save.close();
}
void SavedGamesDisplay(LUDO& l) {
	for (int i = 0; i < l.NoOfPlayers; i++) {
		cout << l.names[i];
		if (i < l.NoOfPlayers - 1) cout << " VS ";
	}
	cout << endl;
}
void OpenSaveGame() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tSAVED GAMES\n";
	ifstream read("SavedGames.ludo", ios::binary);
	read.seekg(0, ios::end);
	short int i = 0;
	LUDO savedludo;
	short int filesize = read.tellg();
	short int numberofGames = filesize / sizeof(LUDO);
	read.seekg(0, ios::beg);
	if (read.fail() or filesize < sizeof(LUDO)) {
		cout << "\t\t0 Saved Games,Play New Games\n\n";
		cout << "\t\tPress any key to back to Main Menu ";
		_getch();
		Menu();
	}
	else {
		while (true)
		{
			read.read((char*)& savedludo, sizeof(LUDO));
			if (read.eof()) break;
			cout << "\t\t" << i + 1 << ". ";
			SavedGamesDisplay(savedludo);
			i++;
		}
		short int choice;
		cout << "Enter Game Number to open Game : ";
		do {
			cin >> choice;
			if (choice <= 0 or choice > numberofGames)
				cout << "Invalid Choice, Enter Again : ";
		} while (choice <= 0 or choice > numberofGames);
		read.seekg(0, ios::beg);
		read.seekg(sizeof(LUDO) * (choice - 1), ios::beg);
		read.read((char*)& savedludo, sizeof(LUDO));
		MainGameplay(savedludo);
	}
	read.close();
}
void Rules() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tRULES\n";
	cout << "\t\t1. The Token will be out only when the Die Number is 6.\n";
	cout << "\t\t2. The Token can't be taken out when there is already a\n\t\tToken of same Player.\n";
	cout << "\t\t3. If the Token of Other Player is Present at Starting Point \n\t\tof Another Player, and The Player Brings the token out"
		"\n\t\tThen the Token Already Present will be killed\n";
	cout << "\t\t4. If the Token Moves to the Position where there is already a \n\t\tToken Present,then the already present token will be killed\n";
	cout << "\t\t5. You will be Given A Bonus Turn if you Bring The Token Out,Kill a Token or \n\t\tif your Token Reached Home\n";
	cout << "\t\t6. There are no stoping point in This LUDO as compared to Traditional LUDO\n";
	cout << "\t\t7. You will also be Given a Bonus Turn on having a Six\n\n\n";
	cout << (ruleoption ? "Press any key to continue" : "Press any key to go back to Main Menu");
	_getch();
	if (ruleoption) {
		ruleoption = false;
		return;
	}
	else
		Menu();
}
void About() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tABOUT\n\n";
	cout << "\t\tThis Game is Created By Muhammad Aizaz Ahmad, a Software Engineering student at P.U.C.I.T\n\n\n";
	cout << "\t\tPress any key to back to Main Menu ";
	_getch();
	Menu();
}
void Menu() {
	system("CLS");
	char choice;
	cout << "\n\n\n\n\n\t\tMAIN MENU\n";
	cout << "\t\t1. PLAY NEW GAME\n";
	cout << "\t\t2. PLAY SAVED GAMES\n";
	cout << "\t\t3. RULES\n";
	cout << "\t\t4. ABOUT\n";
	cout << "\t\t5. EXIT\n\n";
	cout << "\t\tPlease Select Your Option <1-5> : ";
	do {
		choice = _getch();
		cout << endl;
		if (choice != '1' and choice != '2' and choice != '3' and choice != '4' and choice != '5')
			cout << "Please Select Correct Option <1-4> ";
	} while (choice != '1' and choice != '2' and choice != '3' and choice != '4' and choice != '5');
	if (choice == '1')
		NewGame();
	else if (choice == '2')
		OpenSaveGame();
	else if (choice == '3')
		Rules();
	else if (choice == '4')
		About();
	else if (choice == '5')
		exit(0);
}
void StartScreen() {
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t                        _________    _________\n";
	cout << "\t\t\t\t\t|          |        |  |         \\  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|          |        |  |         |  |         |\n";
	cout << "\t\t\t\t\t|________  |________|  |_________/  |_________|\n";
	Sleep(800);
}

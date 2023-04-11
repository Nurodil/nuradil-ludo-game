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

using namespace std;
int indexes[4][4] = { {0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15} };
int startingPoint[4] = { 17,30,56,43 };
int addition[3] = { 22,32,27 };
bool checking = false;
bool anotherchecking = false;
bool TokenOutCheck = false;
bool isWon = false;
bool ruleoption = false;
char TokenOutchoice;
struct LUDO {
	short int NoOfPlayers;
	char tokens[4][4];
	char names[4][20];
	char tokensavailable[4][4];
	char tokenreached[4][4];
	char board[88];
	short int scores[4][4];
	char TokenOut[4][4];
	char starting;
	short int noOfTokens;
};
void TurnDisplay(int player, LUDO& l);
void StartScreen();
void saqlangan(LUDO& l);
void CorrectPosition(int player, int index, int dice, LUDO& l);
int TokensOut(int player, LUDO& l);
void displayboard(LUDO& l);
void TokenReached(int player, int index, LUDO& l);
void intitarray(LUDO& l);
void inputNames(LUDO& l);
void killToken(int playerindex, int player, int position, LUDO& l, int dice);
bool isTokenAvailable(int player, char secenek, LUDO& l);
void TakeTokenOut(int player, LUDO& l);
void movetoken(int player, LUDO& l, int dice);
void MainGameplay(LUDO& l);
void NewGame();
void SavingGame(LUDO l);
void OpenSaveGame();
void Rules();
void About();
void Menu();
void ClearingAndDisplaying(int player, LUDO& l) {
	system("CLS");
	TurnDisplay(player, l);
	displayboard(l);
}

int main() {
	srand((time(0)));
	ShowWindow(GetConsoleWindow(), 3);
	StartScreen();
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 24;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");
	GetCurrentPositionEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
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
int TokensOut(int player, LUDO& l) {
	int count = 0;
	for (int i = 0; i < l.noOfTokens; i++)
		if (l.TokenOut[player][i] != ' ')
			count++;
	return count;
}
void displayboard(LUDO& l) {
	cout << "\t\t\t******************************************************************\n";
	cout << "\t\t\t*            |           |**" << l.board[27] << "**|**" << l.board[28] << "**|**" << l.board[29] << "**|           |           |\n";
	cout << "\t\t\t*     " << l.board[0] << "     |     " << l.board[1] << "     |**" << l.board[26] << "**|**" << l.board[73] << "**|**" << l.board[30] << "**|     " << l.board[4] << "     |     " << l.board[5] << "     |\n";
	cout << "\t\t\t*************|***********|**" << l.board[25] << "**|**" << l.board[74] << "**|**" << l.board[31] << "**|***********|***********|\n";
	cout << "\t\t\t*            |           |**" << l.board[24] << "**|**" << l.board[75] << "**|**" << l.board[32] << "**|           |           |\n";
	cout << "\t\t\t*     " << l.board[2] << "     |     " << l.board[3] << "     |**" << l.board[23] << "**|**" << l.board[76] << "**|**" << l.board[33] << "**|     " << l.board[6] << "     |     " << l.board[7] << "     |\n";
	cout << "\t\t\t*************|***********|**" << l.board[22] << "**|**" << l.board[77] << "**|**" << l.board[34] << "**|***********|***********|\n";
	cout << "\t\t\t*    |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t*  " << l.board[16] << " | " << l.board[17] << " | " << l.board[18] << " | " << l.board[19] << " | " << l.board[20] << " | " << l.board[21] << " |                 | " << l.board[35] << " | " << l.board[36] << " | " << l.board[37] << " | " << l.board[38] << " | " << l.board[39] << " | " << l.board[40] << " |\n";
	cout << "\t\t\t*****|***|***|***|***|***|                 |***|***|***|***|***|***|\n";
	cout << "\t\t\t*    |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t*  " << l.board[67] << " | " << l.board[68] << " | " << l.board[69] << " | " << l.board[70] << " | " << l.board[71] << " | " << l.board[72] << " |     KIZMA BRO   | " << l.board[82] << " | " << l.board[81] << " | " << l.board[80] << " | " << l.board[79] << " | " << l.board[78] << " | " << l.board[41] << " |\n";
	cout << "\t\t\t*****|***|***|***|***|***|                 |***|***|***|***|***|***|\n";
	cout << "\t\t\t*|   |   |   |   |   |   |                 |   |   |   |   |   |   |\n";
	cout << "\t\t\t*  " << l.board[66] << " | " << l.board[65] << " | " << l.board[64] << " | " << l.board[63] << " | " << l.board[62] << " | " << l.board[61] << " |                 | " << l.board[47] << " | " << l.board[46] << " | " << l.board[45] << " | " << l.board[44] << " | " << l.board[43] << " | " << l.board[42] << " |\n";
	cout << "\t\t\t*****|***|***|***|***|***|*****************|***|***|***|***|***|***|\n";
	cout << "\t\t\t*            |           |**" << l.board[60] << "**|**" << l.board[87] << "**|**" << l.board[48] << "**|           |           |\n";
	cout << "\t\t\t*      " << l.board[8] << "     |     " << l.board[9] << "     |**" << l.board[59] << "**|**" << l.board[86] << "**|**" << l.board[49] << "**|     " << l.board[12] << "     |     " << l.board[13] << "     |\n";
	cout << "\t\t\t*************|***********|**" << l.board[58] << "**|**" << l.board[85] << "**|**" << l.board[50] << "**|***********|***********|\n";
	cout << "\t\t\t*            |           |**" << l.board[57] << "**|**" << l.board[84] << "**|**" << l.board[51] << "**|           |           |\n";
	cout << "\t\t\t*     " << l.board[10] << "     |     " << l.board[11] << "     |**" << l.board[56] << "**|**" << l.board[83] << "**|**" << l.board[52] << "**|     " << l.board[14] << "     |     " << l.board[15] << "     |\n";
	cout << "\t\t\t*************|***********|**" << l.board[55] << "**|**" << l.board[54] << "**|**" << l.board[53] << "**|***********|***********|\n";
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
			l.board[i * 4 + j] = token;
			l.tokens[i][j] = token;
			l.tokensavailable[i][j] = token++;
		}
	}
}
void inputNames(LUDO& l) {
	for (int i = 0; i < l.NoOfPlayers; i++) {
		cout << "Oyuncu sayisini girin " << i + 1 << " : ";
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
		cout << l.names[player] << " kazandi!";
		isWon = true;
		return;
	}
	short int dice = rand() % 6 + 1;
	ClearingAndDisplaying(player, l);
	cout << "Bonus: \n";
	cout << "Numara : " << dice << endl;
	if (dice != 6 && !TokensOut(player, l))
		return;
	else if (dice == 6 && !TokensOut(player, l))
		TakeTokenOut(player, l);
	else if (TokensOut(player, l))
		movetoken(player, l, dice);
}
void killToken(int playerindex, int player, int position, LUDO& l, int dice) {
	short int fundice;
	if (l.board[position] != ' ') {
		int i, j, funplayer, index;
		for (i = 0; i < 4; i++)
			for (j = 0; j < l.noOfTokens; j++)
				if (l.tokens[i][j] == l.board[position]) {
					funplayer = i;
					index = j;
					break;
				}
		if (position == startingPoint[funplayer]) {
			cout << (funplayer == player ? "Burda piyon var\n" : "Oyuncu baslangic ​​noktasinda\n");
			if (TokensOut(player, l) >= 2) {
				cout << "Baska Piyon Secin\n"; movetoken(player, l, dice);
				checking = true;
			}
			else {
				checking = true; return;
			}
		}
		else if (funplayer == player) {
			cout << "Kendi oyuncun var\n";
			if (TokensOut(player, l) >= 2) {
				cout << "Baska Piyon Secin\n"; movetoken(player, l, dice);
				checking = true;
			}
			else return;
		}
		else {
			l.board[indexes[funplayer][index]] = l.board[position];
			l.board[position] = ' ';
			l.tokensavailable[funplayer][index] = l.tokens[funplayer][index];
			l.TokenOut[funplayer][index] = ' ';
			l.scores[funplayer][index] = 0;
			if (position == startingPoint[player]) {
				TokenOutCheck = true;
				TakeTokenOut(player, l);
				checking = true;
			}
			fundice = rand() % 6 + 1;
			if (fundice != 6 && !TokensOut(player, l))
				return;
			else if (fundice == 6 && !TokensOut(player, l))
				TakeTokenOut(player, l);
			else if (TokensOut(player, l)) {
				CorrectPosition(player, playerindex, dice, l);
				ClearingAndDisplaying(player, l);
				cout << "Bonus\n";
				cout << "Zar Numarasi : " << fundice << endl;
				movetoken(player, l, fundice);
				checking = true;
			}
		}
	}
}
bool isTokenAvailable(int player, char secenek, LUDO& l) {
	for (int i = 0; i < l.noOfTokens; i++)
		if (l.tokensavailable[player][i] == secenek)
			return true;
	return false;
}
void TakeTokenOut(int player, LUDO& l) {
	if (ReachedCount(player, l) == 4 || TokensOut(player, l) == l.noOfTokens) return;
	 short int index;
	if (!TokenOutCheck) {
		cout << "Zar Secin : ";
		for (int i = 0; i < l.noOfTokens; i++) {
			if (l.tokensavailable[player][i] != ' ')
				cout << l.tokensavailable[player][i] << ' ';
		}cout << ": ";
		do {
			cin >> TokenOutchoice;
			if ((!isTokenAvailable(player, TokenOutchoice, l)))
				cout << "Gecersiz Secim! Baskalarini Secin : ";
		} while (!isTokenAvailable(player, TokenOutchoice, l));
		TokenOutCheck = true;
	}
		for (int i = 0; i < l.noOfTokens; i++)
			if (l.tokens[player][i] == TokenOutchoice)
				index = i;
	short int start = startingPoint[player];
	if (l.board[start] != ' ') {
		killToken(index, player, start, l, 6);
		checking = false;
		TokenOutCheck = false;
	}
	if (TokenOutCheck) {
		l.board[start] = l.board[indexes[player][index]];
		l.board[indexes[player][index]] = ' ';
		l.tokensavailable[player][index] = ' ';
		l.TokenOut[player][index] = TokenOutchoice;
		TokenOutCheck = false;
		short int dice = rand() % 6 + 1;
		ClearingAndDisplaying(player, l);
		cout << "Bonus\nZar Numarasi : " << dice << endl;
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
		if (previous >= 0 && previous <= 10)
			previous += 52;
		if (l.scores[player][index] + dice > 50) {
			MakingPathToHome(player, index, dice, l, previous);
			return;
		}
		if (previous == 67) {
			position = 15 + dice;
			killToken(index, player, position, l, dice);
			if (checking || anotherchecking) { checking = false; anotherchecking = false; return; }
			l.board[position] = l.board[previous];
		}
		else if ((start + l.scores[player][index] + dice > 67)) {
			position = (start + l.scores[player][index] + dice) % 52;
			if (position >= 0 && position <= 10)
				position += 52;
			killToken(index, player, position, l, dice);
			if (checking || anotherchecking) { checking = false; anotherchecking = false; return; }
			l.board[position] = l.board[previous];
		}
		else {
			position = start + l.scores[player][index] + dice;
			killToken(index, player, position, l, dice);
			if (checking || anotherchecking) { checking = false; anotherchecking = false; return; }
			l.board[position] = l.board[previous];
		}
		l.board[previous] = ' ';
	}
	else {
		position = start + l.scores[player][index] + dice;
		killToken(index, player, position, l, dice);
		if (checking || anotherchecking) { checking = false; anotherchecking = false; return; }
		l.board[position] = l.board[previous];
		l.board[previous] = ' ';
	}
	l.scores[player][index] += dice;
}

void movetoken(int player, LUDO& l, int dice) {
	char choiceToken = 'u';
	bool move = true;
	if (dice == 6 && TokensAvailable(player, l)) {
		move = false;
		cout << "Baska bir Piyonu cikartmak ister misiniz? \n Evet y, Hayir n ";
		do {
			choiceToken = _getch();
			cout << endl;
			if (choiceToken != 'y' && choiceToken != 'n')
				cout << "Hata! Sadece y yada n secin : ";
		} while (choiceToken != 'y' && choiceToken != 'n');
	}
	if (choiceToken == 'y')
		TakeTokenOut(player, l);
	else if (choiceToken == 'n' || move) {
		char secenek; short int index;
		cout << "Hangi Piyonu tasimak istiyorsunuz? : ";
		do {
			index = -1;
			cin >> secenek;
			for (int i = 0; i < l.noOfTokens; i++)
				if (l.tokens[player][i] == secenek)
					index = i;
			if (index == -1 || l.TokenOut[player][index] != secenek)
				cout << "Bu piyonu secemezsiniz! Baska birini deneyin : ";
		} while (index == -1 || l.TokenOut[player][index] != secenek);

		if (l.scores[player][index] + dice == 56) {
			cout << "Piyon geldi" << endl;
			TokenReached(player, index, l);
			return;
		}
		else if (l.scores[player][index] + dice > 55) {
			cout << "Ilerleyemezsin\n";
			if (TokensOut(player, l) == 2 || TokensOut(player, l) == 3) {
				cout << "Baska piyonu secin  \n"; movetoken(player, l, dice);
				anotherchecking = true;
			}
			else return;
		}
		CorrectPosition(player, index, dice, l);
		if (dice == 6) {
			dice = rand() % 6 + 1;
			ClearingAndDisplaying(player, l);
			cout << "Bonus\n";
			cout << "Numara : " << dice << endl;
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
	cout << "\t\t\t\t\t\t|  " << name << " Sirasi  |\n";
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
			cout << "Zari atmak icin herhangi bir tusa basin. Oyunu Kaydetmek icin \'S\' tusuna basin ";
			getch = _getch();
			if (getch == 'S') {
				SavingGame(l);
				Menu();
			}
			dice = rand() % 6 + 1;
			cout << "\n" << "Numara :" << dice << endl;
			if ((dice != 6 && !TokensOut(i, l)))
				continue;
			if (dice == 6 && !TokensOut(i, l))
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
	cout << "\n\n\nAna Menuye donmek icin herhangi bir tusa basin";
	_getch();
	Menu();
}
void NewGame() {
	LUDO l;
	system("CLS");
	cout << "Piyon Sayisini Girin (1-4) : ";
	do {
		cin >> l.noOfTokens;
		if (l.noOfTokens <= 0 || l.noOfTokens > 4)
			cout << "En az 1 piyon olmali ";
	} while (l.noOfTokens <= 0 || l.noOfTokens > 4);
	cout << "Oyuncu Sayisini Girin (2-4) : ";
	do {
		cin >> l.NoOfPlayers;
		if (l.NoOfPlayers <= 1 || l.NoOfPlayers > 4)
			cout << "En az 2-4 oyuncu olmali ";
	} while (l.NoOfPlayers <= 1 || l.NoOfPlayers > 4);
	intitarray(l);
	inputNames(l);
	ruleoption = true;
	Rules();
	system("CLS");
	MainGameplay(l);
}
void SavingGame(LUDO l) {
	ofstream save("saqlangan.ludo", ios::app | ios::binary);
	save.write((char*)& l, sizeof(l));
	save.close();
}
void saqlangan(LUDO& l) {
	for (int i = 0; i < l.NoOfPlayers; i++) {
		cout << l.names[i];
		if (i < l.NoOfPlayers - 1) cout << " VS ";
	}
	cout << endl;
}
void OpenSaveGame() {
	system("CLS");
	cout << "\n\n\n\n\n\t\tKAYITLI OYUNLAR\n";
	ifstream read("saqlangan.ludo", ios::binary);
	read.seekg(0, ios::end);
	short int i = 0;
	LUDO savedludo;
	short int filesize = read.tellg();
	short int numberofGames = filesize / sizeof(LUDO);
	read.seekg(0, ios::beg);
	if (read.fail() || filesize < sizeof(LUDO)) {
		cout << "\t\tKayitli Oyunlar,Yeni Oyun\n\n";
		cout << "\t\tAna Menuye donmek icin herhangi bir tusa basin ";
		_getch();
		Menu();
	}
	else {
		while (true)
		{
			read.read((char*)& savedludo, sizeof(LUDO));
			if (read.eof()) break;
			cout << "\t\t" << i + 1 << ". ";
			saqlangan(savedludo);
			i++;
		}
		short int secenek;
		cout << "Oynamak istediginiz oyun numarasini girin : ";
		do {
			cin >> secenek;
			if (secenek <= 0 || secenek > numberofGames)
				cout << "Hata, tekrar deneyin : ";
		} while (secenek <= 0 || secenek > numberofGames);
		read.seekg(0, ios::beg);
		read.seekg(sizeof(LUDO) * (secenek - 1), ios::beg);
		read.read((char*)& savedludo, sizeof(LUDO));
		MainGameplay(savedludo);
	}
	read.close();
}

void Menu() {
	system("CLS");
	char secenek;
	cout << "\n\n\n\n\n\t\tAna Menu\n";
	cout << "\t\t1. Yeni Oyun\n";
	cout << "\t\t2. Kayitli Oyunlar\n";
	cout << "\t\t3. Cik\n\n";
	cout << "\t\tLutfen Secin (1-3) : ";
	do {
		secenek = _getch();
		cout << endl;
		if (secenek != '1' && secenek != '2' && secenek != '3' )
			cout << "Lutfen Dogru Secenegi Secin (1-3) ";
	} while (secenek != '1' && secenek != '2' && secenek != '3' );
	if (secenek == '1')
		NewGame();
	else if (secenek == '2')
		OpenSaveGame();
else if (secenek == '3')
		exit(0);
}

﻿#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>
#include "Morpion.h"
using namespace std;

void Setup() {
	gameover = false;
	null = false;
	ShowCursor(FALSE);
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	nJoueur = 1;
}

void Draw() {
	system("cls");
	cout << "--------" << endl;
	for (int i = 0; i < rows; i++) {
		cout << "|";
		for (int j = 0; j < cols; j++) {
			if (gameGrid[i][j] == 1) {
				cout << "O";
			}
			else if (gameGrid[i][j] == 2) {
				cout << "X";
			}
			else {
				cout << " ";
			}
			cout << "|";
		}

		cout << endl;
		cout << "--------";
		cout << endl;

	}
	cout << "Joueur " << nJoueur << endl;
}

void Input() {
	int row = -1;
	int col = -1;

	GetConsoleScreenBufferInfo(output, &consoleInformation);
	COORD pos = consoleInformation.dwCursorPosition;
	bool ok = false;
	while (!ok) {
		pos.X = 0;
		SetConsoleCursorPosition(output, pos);
		cout << "Entrez la ligne : ";

		int c = _getch();
		if (c - 48 <= rows && c - 48 > 0) {
			ok = true;
			row = c - 49;
		}
	}

	cout << endl;

	ok = false;
	while (!ok) {
		pos.X = 0;
		SetConsoleCursorPosition(output, pos);
		cout << "Entrez la colonne : ";

		int c = _getch();
		if (c - 48 <= cols && c - 48 > 0) {
			ok = true;
			col = c - 49;
		}
	}

	if (gameGrid[row][col] != 0) {
		cout << "Position déja utilisé !";
		string str;
		getline(cin, str);
	}
	else
	{
		gameGrid[row][col] = nJoueur;
		if (nJoueur == 1) {
			nJoueur = 2;
		}
		else
		{
			nJoueur = 1;
		}
	}
}

void Logic() {
	int gagnant;

	// Row J1
	if ((gameGrid[0][0] == 1 || gameGrid[0][0] == 2) && gameGrid[0][1] == gameGrid[0][0] && gameGrid[0][2] == gameGrid[0][0]) { gameover = true; gagnant = gameGrid[0][0]; }
	else if ((gameGrid[1][0] == 1 || gameGrid[1][0] == 2) && gameGrid[1][1] == gameGrid[1][0] && gameGrid[1][2] == gameGrid[1][0]) { gameover = true; gagnant = gameGrid[1][0]; }
	else if ((gameGrid[2][0] == 1 || gameGrid[2][0] == 2) && gameGrid[2][1] == gameGrid[2][0] && gameGrid[2][2] == gameGrid[2][0]) { gameover = true; gagnant = gameGrid[2][0]; }

	// Col 01
	else if ((gameGrid[0][0] == 1 || gameGrid[0][0] == 2) && gameGrid[1][0] == gameGrid[0][0] && gameGrid[2][0] == gameGrid[0][0]) { gameover = true; gagnant = gameGrid[0][0]; }
	else if ((gameGrid[0][1] == 1 || gameGrid[0][1] == 2) && gameGrid[1][1] == gameGrid[0][1] && gameGrid[2][1] == gameGrid[0][1]) { gameover = true; gagnant = gameGrid[0][1]; }
	else if ((gameGrid[0][2] == 1 || gameGrid[0][2] == 2) && gameGrid[1][2] == gameGrid[0][2] && gameGrid[2][2] == gameGrid[0][2]) { gameover = true; gagnant = gameGrid[0][2]; }

	// D0ag 01
	else if ((gameGrid[0][0] == 1 || gameGrid[0][0] == 2) && gameGrid[1][1] == gameGrid[0][0] && gameGrid[2][2] == gameGrid[0][0]) { gameover = true; gagnant = gameGrid[0][0]; }
	else if ((gameGrid[2][0] == 1 || gameGrid[2][0] == 2) && gameGrid[1][1] == gameGrid[2][0] && gameGrid[0][2] == gameGrid[2][0]) { gameover = true; gagnant = gameGrid[2][0]; }

	// Null
	else if (gameGrid[0][0] != 0 && gameGrid[1][0] != 0 && gameGrid[1][1] != 0 && gameGrid[2][0] != 0 &&
		gameGrid[2][1] != 0 && gameGrid[2][2] != 0 && gameGrid[3][0] != 0 && gameGrid[3][1] != 0 &&
		gameGrid[3][2] != 0 && gameGrid[3][3]) {
		gameover = true; null = true;
	}

	if (gameover) {
		Draw();
		cout << endl << "GameOver";
		if (null) {
			cout << endl << "NullGame";
		}
		else
		{
			cout << endl << "Joeur : " << gagnant << " Gagne la partie!";
		}
	}
}

int main()
{
	Setup();
	while (!gameover) {
		Draw();
		Input();
		Logic();
	}
	string str;
	getline(cin, str);
	return 0;
}

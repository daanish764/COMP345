/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#include<iostream>
using namespace std;

#include"GameBoard.h"
#include"StepSingleton.h"

int main()
{
	
	GameBoard gameboard = GameBoard();
	


	while (true)
	{

		gameboard.part1();

		gameboard.part2();

		gameboard.part3();

		gameboard.part4();

		if (gameboard.gameWinCondition() == true) {
			break;
		}
	}


	cout << endl;
	system("PAUSE");
	return 0;
}
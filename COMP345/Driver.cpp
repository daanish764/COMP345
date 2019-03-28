#include<iostream>
using namespace std;

#include"GameBoard.h"

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
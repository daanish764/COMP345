/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#pragma once
#include"Map.h"
#include "Player.h"
class GameBoard 
{
public:
	static int availableRedHouses;
	static int availableGreenHouses;
	static int availableBlueHouses;
	static int availablePurpleHouses;
	static int availableOrangeHouses;
	static int availableYellowHouses;
	static int availableCoal;
	static int availableOil;
	static int availableGarbage;
	static int availableUranium;

	GameBoard();
	void part1();
	void part2();
	void part3();
	void part4();
	void printMarket();
	bool gameWinCondition();
};
/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#pragma once

#include "Observer.h"
#include "Player.h"

class GameStatObserver : public Observer
{
public:
	GameStatObserver();
	GameStatObserver(Player* s, int turn);
	~GameStatObserver();
	void Update();
	void display();
	void nextPhase();
private:
	Player * _subject;
	int turn;
};

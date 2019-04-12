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

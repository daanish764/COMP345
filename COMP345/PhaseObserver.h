#pragma once
#include "Observer.h"
#include "Player.h"
class PhaseObserver: public Observer
{
public:
	PhaseObserver();
	PhaseObserver(Player* s, int turn);
	~PhaseObserver();
	void Update();
	void display();
	void nextPhase();
	

private:

	Player* _subject;
	int turn;
};


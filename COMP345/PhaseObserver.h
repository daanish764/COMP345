#pragma once
#include "Observer.h"
#include "Player.h"
class PhaseObserver: public Observer
{
public:
	PhaseObserver();
	PhaseObserver(Player* s);
	~PhaseObserver();
	void Update();
	void display();

private:

	Player* _subject;
	int turn;
};


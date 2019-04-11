//source of code: "COMP345:Advanced Program Design with C++ Lecture 6: Model View Controller Architecture Observer Pattern" lecture notes. 

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


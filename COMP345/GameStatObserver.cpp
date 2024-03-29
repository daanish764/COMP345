/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/


#include "GameStatObserver.h"
#include "StepSingleton.h"


GameStatObserver::GameStatObserver()
{
}

GameStatObserver::GameStatObserver(Player * s, int turn)
{
	this->turn = turn;
	_subject = s;
	_subject->Attach(this);
}


GameStatObserver::~GameStatObserver()
{
	_subject->Detach(this);
}

void GameStatObserver::Update()
{
	// display();
}

void GameStatObserver::display()
{
	cout << "|------------------------------------------------------------------------------------|	" << endl;
	cout << "\nGAME STAT OBSERVER" << endl;
	cout << "PLAYER INFO          " << endl;
	_subject->getPlayerInfo();
	cout << "Player Network: " << endl;
	_subject->printPlayerNetwork(_subject->getOwnedCities());
	cout << endl;
	cout << "number of houses " << _subject->getOwnedCities().size() << endl;
	_subject->printPlayerGraph(_subject->getOwnedCities());
	cout << endl << "|------------------------------------------------------------------------------------|	" << endl << endl;

}

void GameStatObserver::nextPhase()
{
	turn++;
}

/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#include "PhaseObserver.h"
#include "Player.h"

#include"StepSingleton.h"

PhaseObserver::PhaseObserver()
{
}

PhaseObserver::PhaseObserver(Player* s,int turn) {
	this->turn = turn;
	_subject = s;
	_subject->Attach(this);
}



PhaseObserver::~PhaseObserver()
{
	_subject->Detach(this);
}

void PhaseObserver::Update() {
	display();
}


void PhaseObserver::nextPhase() {
	turn++;
}

void PhaseObserver::display() {

	string stage = "";
	if (turn == 1)
		stage = "";
	if (turn == 2)
		stage = "Phase Status:  AUCTION";
	if(turn == 3)
		stage = "Phase Status:  RESOURCE BUYING";
	if (turn == 4)
		stage = "Phase Status:  BUILDING";
	if (turn == 5)
		stage = "Phase Status:  BUREAUCRACY";

	
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "\n" <<  stage << endl;
		cout << "\n" << "Step #" << StepSingleton::getInstance()->getStep() << endl << endl;
		cout << "Player Info:          " << endl;
		_subject->getPlayerInfo();
		cout << "Player Network: " << endl;
		_subject->printPlayerNetwork(_subject->getOwnedCities());
		cout << endl;
		cout << "number of houses " << _subject->getOwnedCities().size() << endl;
		cout << "|------------------------------------------------------------------------------------|	" << endl << endl;
		
}

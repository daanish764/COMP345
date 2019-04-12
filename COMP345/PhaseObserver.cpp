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

void PhaseObserver::UpdateGameStatus()
{
}


void PhaseObserver::nextPhase() {
	turn++;
}

void PhaseObserver::display() {

	string stage = "";
	if (turn == 1)
		stage = "Phase Status:  DETERMINING PLAYER ORDER";
	if (turn == 2)
		stage = "Phase Status:  AUCTION";
	if (turn == 3)
		stage = "Phase Status:  RESOURCE BUYING";
	if (turn == 4)
		stage = "Phase Status:  BUILDING";
	if (turn == 5)
		stage = "Phase Status:  BUREAUCRACY";

		
		cout << endl << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "\nPHASE OBSERVER" << endl;
		cout << "\n" <<  stage << endl;
		cout << "\n" << "Step #" << StepSingleton::getInstance()->getStep() << endl << endl;
}

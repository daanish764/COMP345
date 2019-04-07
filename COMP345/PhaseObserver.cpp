#include "PhaseObserver.h"
#include "Player.h"



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

	


	if (turn == 1) {
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "		                    Phase Status: " << "DETERMINING PLAYER ORDER" << endl;
		_subject->getPlayerInfo();
		cout << "|------------------------------------------------------------------------------------|	" << endl;
	}

	if (turn == 2) {
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "		                    Phase Status: " << "AUCTION"<< endl;
		_subject->getPlayerInfo();
		cout << "|------------------------------------------------------------------------------------|	" << endl;
	}

	
	if (turn == 3) {
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "		                    Phase Status: " << "RESOURCE BUYING" << endl;
		_subject->getPlayerInfo();
		cout << "|------------------------------------------------------------------------------------|	" << endl;
	}

	if (turn == 3) {
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "		                    Phase Status: " << "RESOURCE BUYING" << endl;
		_subject->getPlayerInfo();
		cout << "|------------------------------------------------------------------------------------|	" << endl;
	}

	if (turn == 4) {
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "		                    Phase Status: " << "BUILDING" << endl;
		_subject->getPlayerInfo();
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		
	}

	if (turn == 5) {
		cout << "|------------------------------------------------------------------------------------|	" << endl;
		cout << "		                    Phase Status: " << "BUREAUCRACY" << endl;
		_subject->getPlayerInfo();
		cout << "|------------------------------------------------------------------------------------|	" << endl;
	}


	
	
}

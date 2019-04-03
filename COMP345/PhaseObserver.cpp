#include "PhaseObserver.h"
#include "Player.h"



PhaseObserver::PhaseObserver()
{
}

PhaseObserver::PhaseObserver(Player* s) {
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

void PhaseObserver::display() {

	turn++;

	cout << "|------------------------------------------------------------------------------------|	" << endl;
	cout << "		                    Phase Status: " << 	turn									  << endl;
	cout << "                                      Player:" << _subject->getName()					  << endl;                                              
	cout << "|------------------------------------------------------------------------------------|	" << endl;
	
}

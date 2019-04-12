/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#pragma once
#include "Observer.h"
#include <list>
using namespace std;
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify() const;
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;
};

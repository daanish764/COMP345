//source of code: "COMP345:Advanced Program Design with C++ Lecture 6: Model View Controller Architecture Observer Pattern" lecture notes.

#pragma once
#include "Observer.h"
#include <list>
using namespace std;
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify() const;
	void NotifyGameStatus() const;
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;
};

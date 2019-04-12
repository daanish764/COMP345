//source of code: "COMP345:Advanced Program Design with C++ Lecture 6: Model View Controller Architecture Observer Pattern" lecture notes.

#include "Subject.h"
#include "Observer.h"
Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};
void Subject::Notify() const {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();
};

void Subject::NotifyGameStatus() const {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->UpdateGameStatus();
};

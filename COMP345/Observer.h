//source of code: "COMP345:Advanced Program Design with C++ Lecture 6: Model View Controller Architecture Observer Pattern" lecture notes.

#pragma once

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
	virtual void UpdateGameStatus() = 0;
protected:
	Observer();
};


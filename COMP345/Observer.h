/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#pragma once

class Observer {
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};


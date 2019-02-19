#pragma once
#include<iostream>
using std::string;

class Player
{
private:
	string name;
public:
	Player();
	Player(string name);
	~Player();
	string getName() const;
};


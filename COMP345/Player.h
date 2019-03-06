#pragma once
#include<iostream>
using std::string;

class Player
{
private:
	string name;
	string color;
	int elektro;
	int coal;
	int garbage;
	int oil;
	int uranium;
public:
	Player();
	Player(string name);
	Player(string name, string houseColor);
	string getHouseColor();
	~Player();
	string getName() const;
	int getElektro();
	
	int getCoal();
	
	int getGarbage();
	
	int getOil();
	
	int getUranium();

	void getPlayerInfo();

	void assignOil(int num);
	void assignGarbage(int num);
	void assignCoal(int num);
	void assignUranium(int num);
	void assignElektro(int num);
};


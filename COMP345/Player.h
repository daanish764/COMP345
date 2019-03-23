#pragma once
#include<iostream>
using std::string;
#include "City.h"

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
	int totalHouses;
	int maxPlants;
	int largestPlant;
	Player();
	Player(string name);
	Player(string name, string color, int maxPlants);
	string getHouseColor();
	~Player();
	string getName() const;
	int getElektro();
	int getCoal();
	int getGarbage();
	int getOil();
	int getUranium();
	string getColor() const;
	void getPlayerInfo();
	void assignOil(int num);
	void assignGarbage(int num);
	void assignCoal(int num);
	void assignUranium(int num);
	void assignElektro(int num);
	void subtractElektro(int num);
	void placeHouse(City* city);
};
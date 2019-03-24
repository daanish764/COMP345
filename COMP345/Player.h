#pragma once
#include<iostream>
using std::string;
#include "City.h"
#include "PowerPlant.h"

class Player
{
private:
	string name;
	string color;
	
public:
	int elektro;
	int coal;
	int garbage;
	int oil;
	int uranium;
	int totalHouses;
	int largestPlant;

	vector<PowerPlant*> ownedPlants;

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
	void assignOil(int num, int cost);
	void assignGarbage(int num, int cost);
	void assignCoal(int num, int cost);
	void assignUranium(int num, int cost);
	void assignElektro(int num);
	void subtractElektro(int num);
	void placeHouse(City* city);
	void buyPlant(PowerPlant* plant, int cost, int maxPlants);
};
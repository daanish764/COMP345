/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#pragma once
#include<iostream>
using std::string;
#include "City.h"
#include "PowerPlant.h"
#include "Subject.h"

class Player: public Subject
{
private:
	string name;
	string color;
	vector<City*> ownedCities;
	
public:
	int elektro;
	int coal;
	int garbage;
	int oil;
	int uranium;
	int totalHouses;
	int largestPlant;
	int poweredCities;
	City* startCity;

	vector<PowerPlant*> ownedPlants;

	Player();
	Player(string name);
	Player(string name, string color, int maxPlants);
	string getHouseColor();
	~Player();
	string getName() const;
	City* getStartCity();
	void setStartCity(City* startCity);
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
	void printPhaseStatus();

	bool isConnectedToCity(City* city);
	void connectToCity(City* city);
	vector<City*> getOwnedCities();
};
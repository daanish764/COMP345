#pragma once
#include<iostream>
#include<vector>
#include"Player.h"

using std::string;
using std::vector;

class City
{
private:
	

public:
	string cityName;
	vector<City*> adjacentCities;
	Player* owner;

	int redHouse;
	int greenHouse;
	int blueHouse;
	int purpleHouse;
	int orangeHouse;
	int yellowHouse;

	City();
	City(string cityName);
	City(string cityName, Player* player);
	~City();
	
	void setCityName(string cityName);
	string getCityName() const;
	string getCityStatus();

	void placeRedHouse();
	void placeGreenHouse();
	void placeBlueHouse();
	void placePurpleHouse();
	void placeOrangeHouse();
	void placeYellowHouse();


	void addAdjacentCity(City* city);
	vector<City*> getAdjacentCities() const;

	void removeAdjacentCity(City* city);

	void setOwner(Player * player);
	Player* getOwner() const;

};


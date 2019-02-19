#pragma once
#include<iostream>
#include<vector>
#include"Player.h"

using std::string;
using std::vector;

class City
{
private:
	string cityName;
	vector<City*> adjacentCities;
	Player* owner;

public:
	City();
	City(string cityName);
	City(string cityName, Player* player);
	~City();
	
	void setCityName(string cityName);
	string getCityName() const;


	void addAdjacentCity(City* city);
	vector<City*> getAdjacentCities() const;

	void removeAdjacentCity(City* city);

	void setOwner(Player * player);
	Player* getOwner() const;

};


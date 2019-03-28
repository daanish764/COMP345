/*
Team 24

Daanish Rehman [27027753]
Jawed Bhojani [29060936]
Kadeem Caines [26343600]
*/

#pragma once
#include<iostream>
#include<vector>

using std::string;
using std::vector;

class City
{
private:
	string cityName;
	vector<City*> adjacentCities;
	vector<int> cost;
	
public:

	int redHouse;
	int greenHouse;
	int blueHouse;
	int purpleHouse;
	int orangeHouse;
	int yellowHouse;

	City();
	City(string cityName);
	~City();
	
	void setCityName(string cityName);
	string getCityName() const;


	void addAdjacentCity(City* city, int cost);
	vector<City*> getAdjacentCities() const;
	void removeAdjacentCity(City* city);
	void printAllAdjacentCities();
	string getCityStatus();

	void placeRedHouse();
	void placeGreenHouse();
	void placeBlueHouse();
	void placePurpleHouse();
	void placeOrangeHouse();
	void placeYellowHouse();
	int getNumberOfHouses(string color);
	int getNumberOfHouses();
	void placeHouse(string color);
};


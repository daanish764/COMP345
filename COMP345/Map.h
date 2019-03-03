#pragma once

#include<iostream>
#include<vector>
#include"City.h"
using std::string;
using std::vector;

class Map
{
private:
	vector<City*> cityList;
	City* firstCity;
public:
	static int availableRedHouses;
	static int availableGreenHouses;
	static int availableBlueHouses;
	static int availablePurpleHouses;
	static int availableOrangeHouses;
	static int availableYellowHouses;
	static int availableCoal;
	static int availableOil;
	static int availableGarbage;
	static int availableUranium;
	Map();
	~Map();
	void addCity(City* city);
	void removeCity(City* city);
	const void connectCity(City* city1, City* city2);
	const bool allCitiesConnected() const;
	const void printAllCities() const;
	City* getCity(const string cityName);
	vector<City*> getCityList();
};


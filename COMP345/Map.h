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
	Map();
	~Map();
	void addCity(City* city);
	void removeCity(City* city);
	const void connectCity(City* city1, City* city2, int cost);
	const bool allCitiesConnected() const;
	const void printAllCities() const;
	City* getCity(const string cityName);
	vector<City*> getCities() const;
	
};


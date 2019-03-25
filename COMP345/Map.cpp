#include<iostream>
#include<string>
#include"Map.h"
#include"City.h"
#include<vector>
#include<unordered_map> 
#include<map>
#include<stack>
#include<algorithm>

using namespace std;

Map::Map()
{
}


Map::~Map()
{
	
}

void Map::addCity(City * city)
{
	bool alreadyAdded = false;

	for (unsigned int i = 0; i < cityList.size(); i++)
	{
		if (cityList[i]->getCityName() == city->getCityName())
		{
			alreadyAdded = true;
		}
		if (alreadyAdded)
			break;
	}

	if (firstCity == NULL) {
		firstCity = city;
	}

	if (!alreadyAdded)
	{
		cityList.push_back(city);
	}
}

void Map::removeCity(City * city)
{
	for (unsigned int i = 0; i < cityList.size(); i++) {
		if (cityList.at(i) == city)
		{
			cityList.erase(cityList.begin() + i);
		}
	}
}

const void Map::connectCity(City* city1, City* city2, int cost)
{

	if (getCity(city1->getCityName()) != NULL)
	{
		city1 = getCity(city1->getCityName());
	}
	if (getCity(city2->getCityName()) != NULL)
	{
		city2 = getCity(city2->getCityName());
	}
	city1->addAdjacentCity(city2, cost);
	city2->addAdjacentCity(city1, cost);
}

const bool Map::allCitiesConnected() const {
	int counter = 0;
	int size = cityList.size();
	unordered_map<City*, bool> visited;

	for (unsigned int i = 0; i < cityList.size(); i++) {
		City * currentCity = cityList.at(i);
		visited[currentCity] = false;
	}

	City* currentCity = firstCity;

	stack<City*> cityStack;

	cityStack.push(firstCity);

	while(!cityStack.empty())
	{
		City* currentCity = cityStack.top();
		cityStack.pop();

//		cout << "current city : " << currentCity->getCityName() << endl;

		vector<City*> currentCityNeighbors = currentCity->getAdjacentCities();

		
		for (unsigned int i = 0; i < currentCityNeighbors.size(); i++) {
			City* currentNeighborCity = currentCityNeighbors.at(i);
//			cout << currentCity->getCityName() <<" city has neighbors " << currentNeighborCity->getCityName() << endl;
			if (visited[currentNeighborCity] == false)
			{
				cityStack.push(currentNeighborCity);
			}
		}

		visited[currentCity] = true;

//		cout << "the size of the cityStack is " << cityStack.size() << endl;
		if (cityStack.size() != 0)
		{
//			cout << "the top of the cityStack is " << cityStack.top()->getCityName() << endl;
		}
		
	}

	int countConnectedCities = 0;

//	cout << "---------VISITED---------"<<endl;
	for (auto x : visited)
	{
//		cout << x.first << "\t" << x.second << endl;
		
		if (x.second == true) {
			countConnectedCities++;
		}
	}

//	cout << "---------VISITED---------" << endl;

	if (countConnectedCities == cityList.size()) {
//		cout << "size of visited = " << countConnectedCities << endl;
//		cout << "size of cityList " << cityList.size() << endl;
//		cout << "yes everything is connected" << endl;
		return true;
	}
	else {
//		cout << "size of visited = " << countConnectedCities << endl;
//		cout << "size of cityList " << cityList.size() << endl;
//		cout <<"no not connected" << endl;
		return false;
	}
}

const void Map::printAllCities() const {
	cout << "Printing all cities in the Map class" << endl;
	for (unsigned int i = 0; i < cityList.size(); i++)
	{
		
		cout << "City  " << i << ":" << cityList[i]->getCityName() << endl;
	}
}

City* Map::getCity(string cityName)
{
	for (unsigned int i = 0; i < cityList.size(); i++)
	{
		if (cityList[i]->getCityName() == cityName)
		{
			return cityList[i];
		}

	}
	return NULL;
}

vector<City*> Map::getCities() const
{
	return this->cityList;
}

vector<City*> Map::getConnectableCities(City* city, string color)
{
	vector<City*> result;
	// if there is no house on the starting city, we simply add it to result vector and return the result
	if (city->getNumberOfHouses() == 0)
		result.push_back(city);
	else
	{
		// loop over all adjacent cities and if there is no house on the 
		vector<City*> adjCities = city->getAdjacentCities();

		for (int i = 0; i < adjCities.size(); i++)
		{
			// if the city is already in the vector we dont want to insert it twice
			if (std::find(result.begin(), result.end(), adjCities.at(i)) != result.end())
				continue;

			// if there is no house on the city we would like to add it
			if (adjCities.at(i)->getNumberOfHouses() == 0)
				result.push_back(adjCities.at(i));
		}
	}

	return result;
}

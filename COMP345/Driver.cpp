#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

#include"City.h"
#include"Map.h"
#include"Player.h"

bool readMapFromFile(Map* map, string file)
{
	ifstream myFile;

	vector<string> cities;

	myFile.open("data.txt");

	string line;
	if (myFile.is_open())
	{
		while (myFile >> line)
		{
			cities.push_back(line);
		}
	}
	else {
		cout << "ERROR: could not open file" << endl;
	}

	myFile.close();

	for (unsigned int i = 0; i < cities.size(); i = i + 2)
	{
		cout << cities[i] << " -> " << cities[i + 1] << endl;

		City* firstCity = new City(cities[i]);
		City* secondCity = new City(cities[i + 1]);

		map->addCity(firstCity);
		map->addCity(secondCity);

		map->connectCity(firstCity, secondCity);

	}

	map->printAllCities();

	if (map->allCitiesConnected())
	{
		cout << "Yes, everything is connected." << endl;
		return true;
	}
	else
	{
		cout << "Nope, not connected WTF" << endl;
		return false;
	}

}


int main()
{
	// creating a Map
	Map map = Map();

	/*
	// PART 1 
	Player Johnathan = Player("Johnathan");
	Player Micheal = Player("Micheal");
	Player Austin = Player("Austin");
	Player Catherine = Player("Catherine");

	cout << "--------- THE PLAYERS ARE --------" << endl;
	cout << Johnathan.getName() << endl;
	cout << Micheal.getName() << endl;
	cout << Austin.getName() << endl;
	cout << Catherine.getName() << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;

	City montrealCity = City("Montreal", &Johnathan);
	City lavalCity = City("Laval", &Micheal);
	City torontoCity = City("Toronto", &Austin);
	City HamiltonCity = City("Hamilton", &Catherine);

	map.addCity(&montrealCity);
	map.addCity(&lavalCity);
	map.addCity(&torontoCity);
	map.addCity(&HamiltonCity);

	cout << "--------- THE CITIES ARE --------" << endl;
	cout << montrealCity.getCityName() << endl;
	cout << lavalCity.getCityName() << endl;
	cout << torontoCity.getCityName() << endl;
	cout << HamiltonCity.getCityName() << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;

	cout << "we are connecting cities now" << endl;
	cout << "-----------------------------------" << endl;

	cout << "montrealCity -> lavalCity" << endl;
	montrealCity.addAdjacentCity(&lavalCity);

	cout << "lavalCity -> montrealCity" << endl;
	lavalCity.addAdjacentCity(&montrealCity);

	cout << "montrealCity -> HamiltonCity" << endl;
	montrealCity.addAdjacentCity(&HamiltonCity);

	cout << "HamiltonCity -> torontoCity" << endl;
	HamiltonCity.addAdjacentCity(&torontoCity);
	cout << "-----------------------------------" << endl;
	cout << endl;

	cout << "let check if all cities are connected " << endl;
	if (map.allCitiesConnected())
	{
		cout << "yes all the cities are connected " << endl;
	}
	else {
		cout << "no all the cities are not connected " << endl;
	}

	cout << endl;
	cout << "let remove a connection." << endl;

	HamiltonCity.removeAdjacentCity(&torontoCity);
	cout << "HamiltonCity -x torontoCity" << endl;

	cout << endl;

	cout << "let check if all cities are connected." << endl;

	if (map.allCitiesConnected())
	{
		cout << "yes all the cities are connected " << endl;
	}
	else {
		cout << "no all the cities are not connected " << endl;
	}



	City* cityX = map.getCity("Montreal");

	cout << cityX->getCityName() << endl;
	

	*/


	

	if (readMapFromFile(&map, "data.txt"))
	{
		cout << "success" << endl;
	}
	else
	{
		cout << "failure" << endl;
	}

	

	cout << endl;
	system("PAUSE");
	return 0;
}
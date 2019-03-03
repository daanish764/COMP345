#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>    // std::random_shuffle for shuffling the deck (Part 5)
#include <ctime>		// used for shuffling
#include <map>
using namespace std;

#include"City.h"
#include"Map.h"
#include"Player.h"
#include"PowerPlant.h"
#include"OverviewCard.h"

vector<PowerPlant*> deck; //Vector where all the powerplant and 'Step 3' card will be (Part 5)

int Map::availableRedHouses = 22;
int Map::availableGreenHouses = 22;
int Map::availableBlueHouses = 22;
int Map::availablePurpleHouses = 22;
int Map::availableOrangeHouses = 22;
int Map::availableYellowHouses = 22;
int Map::availableCoal = 24;
int Map::availableOil = 24;
int Map::availableGarbage = 24;
int Map::availableUranium = 12;

//Shuffling the deck (Part 5)
void Shuffle() {
	random_shuffle(deck.begin(), deck.end());
}

// Printing the deck (Part 5)
void printDeck()
{
	/*for (std::vector<PowerPlant*>::iterator i = deck.begin(); i != deck.end(); ++i) {
		cout << *i << ' ';
	}*/

	for (int i = 0; i < deck.size(); i++) {
		cout << deck[i]->getPlantNumber() << ' ';
	}

}

bool readMapFromFile(Map* map, string file)
{
	ifstream myFile;

	vector<string> cities;

	myFile.open("data.txt");

	string line;
	if (myFile.is_open())
	{
		while (myFile >> line && line != "####")
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

	//PART 2
	if (readMapFromFile(&map, "data.txt"))
	{
		cout << "success" << endl;
	}
	else
	{
		cout << "failure" << endl;
	}


	//PART 3
	


	cout << "\n\n***PART 3";
	cout << "\n***Lets print Montreal's current status\n";
	cout << map.getCity("Montreal")->getCityStatus();

	cout << "\n\n***Printing Montreal status after adding a red and blue house\n";

	map.getCity("Montreal")->placeRedHouse();
	map.getCity("Montreal")->placeBlueHouse();
	cout << map.getCity("Montreal")->getCityStatus() + "\n\n";


	cout << "\n\n***Lets add more houses to more cities and print status of all cities and resources\n";
	map.getCity("Toronto")->placeGreenHouse();
	map.getCity("Edmonton")->placeYellowHouse();
	map.getCity("Calgary")->placeOrangeHouse();
	map.getCity("Calgary")->placePurpleHouse();
	map.getCity("Houston")->placeGreenHouse();
	map.getCity("Houston")->placeOrangeHouse();


	vector<City*> cityList = map.getCityList();
	for (int i = 0; i < cityList.size(); i++) {
		cout << cityList[i]->getCityStatus() << ' ';
	}

	cout << "\n\n***AVAILABLE HOUSES";
	string availHouses = ("\nRed Houses: " + std::to_string(Map::availableRedHouses) + " | Green Houses: " + std::to_string(Map::availableGreenHouses) + " | Blue Houses: " + std::to_string(Map::availableBlueHouses)
		+ " | Purple Houses: " + std::to_string(Map::availablePurpleHouses) + " | Orange Houses: " + std::to_string(Map::availableOrangeHouses) + " | Yellow Houses: " + std::to_string(Map::availableYellowHouses));
	cout << availHouses;

	cout << "\n\n***AVAILABLE RESOURCES";
	string availRes = ("\nCoal: " + std::to_string(Map::availableCoal) + " | Oil: " + std::to_string(Map::availableOil) + " | Garbage: " + std::to_string(Map::availableGarbage) + " | Uranium: " + std::to_string(Map::availableUranium));
	cout << availRes;

	
	
	cout << "\n\n***Saving city and resource status onto the game map (check txt file)\n";
	std::ofstream out;
	
	out.open("data.txt", std::ios::app);
	for (int i = 0; i < cityList.size(); i++) {
		std::string str = (cityList[i]->getCityStatus());
		out << str;
	}
	out << "\n\n####";
	out << availHouses;
	out << availRes;
	

	//PART 5

	cout << "\n\n***PART 5\n";
	
	//Creating the 43 powerplant cards

	/*
	CARD NUMBER 0 IS THE PHASE 3/STEP 3 CARD. It would have made little sense to create a new class for it since it has no real properties or owner. It makes sense to keep it with the powerplants because it is kept
	in the deck with the powerplant cards and looks like a powerplant card from the back so it's like a "surprise draw": you think you're gonna pull a powerplant but it could be the Step 3 card.
	*/

	for (int i = 1; i <= 43; i++) //for loop creates the powerplant cards only(1 to 43) and pushes them to the deck vector (deck vector created at the top of this file)
	{
		PowerPlant* plant = new PowerPlant(i);
		deck.push_back(plant);
	}

	cout << "\n***Printing the deck of powerplants pre-shuffle:\n\n";
	printDeck();

	//Shuffling the deck
	srand(unsigned(std::time(0))); //C++ random is not truly random and you'd get the same shuffle each time. So we are using the current time as seed to get new shuffle patterns.
	Shuffle();

	cout << "\n\n***Printing the deck of powerplants post-shuffle:\n\n";
	printDeck();



	//creating the Step 3 card and inserting it at the bottom of the deck where it belongs after the shuffle
	PowerPlant* Step3 = new PowerPlant(0);
	deck.insert(deck.begin(), Step3);

	cout << "\n\n***Printing deck after inserting the Step 3 Card (Card number 0) at the bottom of the deck:\n\n";
	printDeck();
	


	cout << "\n\n***Now we are taking the top powerplant of the deck and assigning it to player John and using getOwner() method:\n\n";
	Player* player1 = new Player("John");
	
	int topCard = deck.size() - 1;
	deck[topCard]->setOwner(player1);
	cout << "The owner of powerplant number "<< deck[topCard]->getPlantNumber() <<" is: " << deck[topCard]->getOwner()->getName();


	//Creating and assigning the overview cards
	/*
	Images of the back and front of the overview cards: https://imgur.com/a/e1ChGtM  
	I spoke about these cards with the prof on 28th Feb 2019. In real life, these cards are handed out to each player as a guide as to what the phases are and how much money they'll receive in phase 5(bureaucracy)
	of the game. So basically, these are useless to the more experienced player and probably get tossed aside (or not even distributed) while playing. But the professor wants to see them in the game and wants 
	it handed out to each player as she sees it like a player 'ID'. So the only property this card has is the card owner..
	*/

	//Lets create two overview cards for a 2 player game. I'll assign one of them to John since he's already created.
	
	vector<OverviewCard*> players; //storage for overview card pointers. Basically where all the players lie. We will probably use this vector in the future to determine/switch player order etc.

	OverviewCard* idCard1 = new OverviewCard(1);
	idCard1->setOwner(player1); //player1 aka john

	Player* player2 = new Player("Marcos");
	OverviewCard* idCard2 = new OverviewCard(2);
	idCard2->setOwner(player2);

	/*
	cout << "\n-----\n";
	idCard2->printDescription();
	cout << "\n-----\n";
	*/
	//placing the id/overview cards into the vector
	players.push_back(idCard1);
	players.push_back(idCard2);


	cout << "\n\n***Overview cards created and assigned to players John and Marcos(for a 2 player game).\n";
	cout << "***Printing all participants' names via OverviewCard's getOwner() method:\n\n";
	for (int i = 0; i < players.size(); i++) {
		cout << "Player " << i+1 << ": " << players[i]->getOwner()->getName() << '\n';
	}

	cout << endl;
	system("PAUSE");
	return 0;
}
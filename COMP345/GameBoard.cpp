#include<iostream>
#include <ctime>
#include<stdlib.h>
#include<map>
#include<algorithm>
#include<set>
#include<fstream>
#include<sstream>

#include<vector>
#include"Player.h"
#include"Map.h"
#include"GameBoard.h"
#include"PowerPlant.h"

using std::cout;
using std::endl;
using std::cin;
using std::pair;

int GameBoard::availableRedHouses = 22;
int GameBoard::availableGreenHouses = 22;
int GameBoard::availableBlueHouses = 22;
int GameBoard::availablePurpleHouses = 22;
int GameBoard::availableOrangeHouses = 22;
int GameBoard::availableYellowHouses = 22;
int GameBoard::availableCoal = 24;
int GameBoard::availableOil = 24;
int GameBoard::availableGarbage = 24;
int GameBoard::availableUranium = 12;

vector<PowerPlant*> market;

// the deck of the powerplant cards
std::vector<PowerPlant*> deck;

// a pointer that points to an vector of all the players
vector<Player*> players;

// Vector for all powerplants
vector<PowerPlant*> powerplants;

// number of Players playing the game
int numberOfPlayer = 0;

// the connected map with all the cities 
Map* citiesMap;

//Summary card/array. Absolutely see the rulebook to know exactly what this is.
const int summaryCard[5][5] = {	{2, 3, 4, 5, 6},		// number of regions/players (set according to assignment requirement, not official rules)
							{8, 8, 4, 0, 0},		// number of plant cards to remove randomly from deck
							{4, 3, 3, 3, 3},		// maximum number of powerplants a player can own
							{10, 7, 7, 7, 6},		// number of connected cities to trigger STEP 2
							{21, 17, 17, 15, 14}, };// number of connected cities to trigger GAME END.


//Prices that need to be charged for COAL, OIL and GARBAGE; i.e. charge $1 if 22 or more are available, $2 if 19 or more are available etc.
const int priceList1[2][8] = { {22, 19, 16, 13, 10, 7, 4, 1},
								{1, 2, 3, 4, 5, 6, 7, 8} };

//Prices that need to be charged for URANIUM; same concept as priceList1
const int priceList2[2][12] = { {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
								{1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16} };

void setUpPowerPlantCards();
int getPowerPlant(int x);
void getBoardStatus(vector<City*> cities);
void printPlayerNetwork(Player* player, vector<City*> cityList);
void printPlayerPlants(Player* player);
void printDeck();
void sortPlayersDescending();
void sortPlayersAscending();
void sortMarket();

//phase3 functions
int getCoalCost();
int getOilCost();
int getGarbageCost();

bool readMapFromFile(Map* map, string file, int numberOfPlayer);

void GameBoard::part1()
{
	string trash;
	vector<City*> cities = citiesMap->getCities();
	cout << "\n----PLAYER STATUS LIST-----" << endl;
	for (int i = 0; i < numberOfPlayer; i++)
	{
		players[i]->getPlayerInfo();
		
		printPlayerNetwork(players[i], cities);

		cout << "\n\n" << endl;
	}
	cout << "----END----\n" << endl;

	setUpPowerPlantCards();
	cout << "\n***The Plantdeck has been shuffled, " << summaryCard[1][numberOfPlayer - 2] << " cards have been randomly removed and Step 3 card has been put at the bottom and plant 13 at the top.\n";

	//getBoardStatus(cities);
}

void GameBoard::part2()
{
	cout << "\n\nPHASE 1: DETERMINING PLAYER ORDER" << endl << endl;

	sortPlayersDescending(); //sorts by total houses owned. Ties broken by largest plant owned.
	cout << "***Players with most houses go first. Ties are broken by largest plant owned. Else the order remains intact." << endl;

	//display new order
	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << (i + 1) << ". " << players[i]->getName() << " with " << players[i]->totalHouses << " house(s). Largest plant owned: " << players[i]->largestPlant << endl;
	}

	cout << "\n\nPHASE 2: AUCTION" << endl;

	int chosenPlant = 0;
	vector<Player*> activeAtAuction = players;

	//WHILE LOOP FOR PEOPLE WHO ARE STILL ACTIVE IN PHASE 2 A.K.A HAVE NOT PASSED OR WON A POWERPLANT YET.
	while (activeAtAuction.size() > 0) {
		cout << endl << endl;
		printMarket();
		cout << "It's " << activeAtAuction[0]->getName() << "'s turn." << endl;

		//if the person can't even afford the cheapest plant in the market, we take him/her out of the auction entirely
		if (market[0]->getPlantNumber() > activeAtAuction[0]->getElektro()) {
			cout << "This player can't afford the cheapest powerplant on the market. Taking out of auction." << endl;
			activeAtAuction.erase(activeAtAuction.begin());
		}
		else {
			while (getPowerPlant(chosenPlant) == -1 || chosenPlant > activeAtAuction[0]->getElektro()) { //getPowerPlant == -1 means its not a valid plant from the actual market. 
				cout << "Please choose the power plant(you can afford) to bid on from actual market or enter 0 to pass and sit out entirely: ";
				cin >> chosenPlant;
				if (chosenPlant == 0) { break; }
			}

			if (chosenPlant == 0) {
				cout << "Chose to Pass" << endl;
				activeAtAuction.erase(activeAtAuction.begin());
			}
			else {
				cout << "\nPOWERPLANT BEING AUCTIONED: " << chosenPlant << endl;


				vector<Player*> activeBidders = activeAtAuction;
				int currentBid = 0;
				int highestBid = 0;
				int currentBidder = 0;

				//THE AUCTION WHILE LOOP. ENDS WHEN THERE'S ONE BIDDER LEFT
				while (activeBidders.size() > 1) {
					cout << "It's " << activeBidders[currentBidder]->getName() << "'s turn to place a bid on plant " << chosenPlant << ". Enter a bid: ";
					cin >> currentBid;

					//ensures the auction starter bids minimum the plant value AND people don't bid over than what they have
					currentBid = std::min(std::max(currentBid, chosenPlant), activeBidders[currentBidder]->getElektro()); 

					if (currentBid <= highestBid) { //Bad bid. Lower than or equal to  highest bid
						cout << "Chose to sit out of current bidding war.\n" << endl;
						activeBidders.erase(activeBidders.begin() + currentBidder); // Taking the quitter out of the activeBidders
						if (currentBidder == activeBidders.size()) { //if the person bailing out is the last person in the queue, point back to the first person in queue
							currentBidder = 0;
						}
					}
					else { //If it's a good bid
						cout << activeBidders[currentBidder]->getName() << " bid " << currentBid << ".\n" << endl;
						currentBidder = (currentBidder + 1) % activeBidders.size(); //point to the next person to ask their bid
						highestBid = currentBid; //the current bid is now the highest bid
					}
				}
				//*******************AUCTION HAS ENDED. NOW TIME TO ASSIGN THE WINNER THE POWERPLANT AND REPLACE THE POWERPLANT FROM ACTUAL MARKET

				//assign powerplant owner here at activeBidders[0]. Basically the last active bidder
				market[getPowerPlant(chosenPlant)]->setOwner(activeBidders[0], std::max(chosenPlant, highestBid));
				cout << "Powerplant " << chosenPlant << " bought by " << activeBidders[0]->getName() << " for " << std::max(chosenPlant, highestBid) << " Elektros!" << endl;


				//replacing the won powerplant with the top card of the deck
				market[getPowerPlant(chosenPlant)] = deck[deck.size() - 1];

				//Sort the future/actual market
				sortMarket();

				//Now to pop the top card of the deck, out of the deck
				deck.pop_back();

				//Now we also have to take out the winner out of activeAtAuction because their phase 2 is done.
				for (int i = 0; i < activeAtAuction.size(); i++) {
					if (activeAtAuction[i] == activeBidders[0]) {
						activeAtAuction.erase(activeAtAuction.begin() + i);
					}
				}
			}
		}
	}
	//Lets see the possessions all the player own

	vector<City*> cities = citiesMap->getCities();

	cout << "\n***Lets see what each player owns at this point:\n";
	for (int i = 0; i < players.size(); i++) {
		cout << endl << endl;
		players[i]->getPlayerInfo();
		printPlayerPlants(players[i]);
		printPlayerNetwork(players[i], cities);
	}
}

void GameBoard::part3() {
	cout << "\n\nPHASE 3: RESOURCE BUYING" << endl << endl;

	sortPlayersAscending(); //sorts by total houses owned. Ties broken by largest plant owned. But in reverse order than previously done
	cout << "***Players with least houses go first. Ties are broken by smallest plant owned. Else the order remains intact." << endl;

	//display new order
	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << (i + 1) << ". " << players[i]->getName() << " with " << players[i]->totalHouses << " house(s). Largest plant owned: " << players[i]->largestPlant << endl;
	}

	for (int k = 0; k < players.size(); k++){
		//Capacity for one player to carry any resource given there powerplants
		int coalCapacity = 0;
		int oilCapacity = 0;
		int garbageCapacity = 0;
		int uraniumCapacity = 0;
		
		//The amounts the player is looking to buy
		int coalBuy = 0;
		int oilBuy = 0;
		int garbageBuy = 0;
		int uraniumBuy = 0;

		
		for (int i = 0; i < powerplants.size(); i++) {
			if (powerplants[i]->getOwner() == players[k]) {
				coalCapacity += (powerplants[i]->coalRequired * 2) - players[k]->getCoal();
				oilCapacity += (powerplants[i]->oilRequired * 2) - players[k]->getOil();
				garbageCapacity += (powerplants[i]->garbageRequired * 2) - players[k]->getGarbage();
				uraniumCapacity += (powerplants[i]->uraniumRequired * 2) - players[k]->getUranium();
			}
		}
		cout << "\n\n" << players[k]->getName() << "'s total storage capacity for each resource given his/her power plants, minus current resources owned:";
		cout << "\nCoal Capacity : " << coalCapacity << endl;
		cout << "Oil Capacity : " << oilCapacity << endl;
		cout << "Garbage Capacity : " << garbageCapacity << endl;
		cout << "Uranium Capacity : " << uraniumCapacity << endl;
		cout << endl;

		cout << "\nPlease enter the amount of COAL you want to buy:";
		cin >> coalBuy;

		coalBuy = std::min(coalCapacity, coalBuy);

		while (coalBuy > 0) {
			cout << "\n Acquired 1 coal for " << getCoalCost() << " Elektros";
			players[k]->assignCoal(1, getCoalCost());
			coalBuy -= 1;
		}

		cout << "\nPlease enter the amount of OIL you want to buy:";
		cin >> oilBuy;

		oilBuy = std::min(oilCapacity, oilBuy);

		while (oilBuy > 0) {
			cout << "\n Acquired 1 oil for " << getOilCost() << " Elektros";
			players[k]->assignOil(1, getOilCost());
			oilBuy -= 1;
		}

		cout << "\nPlease enter the amount of GARBAGE you want to buy:";
		cin >> garbageBuy;

		garbageBuy = std::min(garbageCapacity, garbageBuy);

		while (garbageBuy > 0) {
			cout << "\n Acquired 1 garbage for " << getGarbageCost() << " Elektros";
			players[k]->assignGarbage(1, getGarbageCost());
			garbageBuy -= 1;
		}
	}

	//Lets see the possessions all the player own

	vector<City*> cities = citiesMap->getCities();

	cout << "\n***Lets see what each player owns at this point:\n";
	for (int i = 0; i < players.size(); i++) {
		cout << endl << endl;
		players[i]->getPlayerInfo();
		printPlayerPlants(players[i]);
		printPlayerNetwork(players[i], cities);
	}

	
}

int getCoalCost() {
	for (int i = 0; i < 8; i++) {
		if (GameBoard::availableCoal >= priceList1[0][i]) {
			return priceList1[1][i];
		}
	}
}

int getOilCost() {
	for (int i = 0; i < 8; i++) {
		if (GameBoard::availableOil >= priceList1[0][i]) {
			return priceList1[1][i];
		}
	}
}

int getGarbageCost() {
	for (int i = 0; i < 8; i++) {
		if (GameBoard::availableGarbage >= priceList1[0][i]) {
			return priceList1[1][i];
		}
	}
}

bool readMapFromFile(Map* map, string file, int numberOfPlayer) //number of players == number of regions
{
	std::ifstream infile;

	infile.open(file);

	string city1, city2;
	int cost;

	cout << "\n*** Loading " << numberOfPlayer << " adjacent regions and the connections between them with connection cost..." << endl;
	while (infile >> city1 >> city2 >> cost)
	{
		City* firstCity = new City(city1);
		City* secondCity = new City(city2);

		cout << firstCity->getCityName() << " -> " << secondCity->getCityName() << " (" << cost << ")" << endl;

		map->addCity(firstCity);
		map->addCity(secondCity);

		map->connectCity(firstCity, secondCity, cost);

		if (map->getCities().size() == (numberOfPlayer * 7)) { //7 cities per number of players/region
			break;
		}
	}


	infile.close();

	if (map->allCitiesConnected())
	{
		// cout << "Yes, everything is connected." << endl;
		return true;
	}
	else
	{
		cout << "Invalid Map File" << endl;
		return false;
	}

}

int getPowerPlant(int x) //used to be isValidCard. Serves similar purpose. Tells the location of powerplant in the actual market.
{
	for (int i = 0; i < 4; i++) //can only bid on the first 4 cards of the market aka the actual market. Else the card is invalid.
	{
		if (market[i]->getPlantNumber() == x)
		{
			return i;
		}
	}
	return -1;
}

void GameBoard::printMarket()
{

	cout << "The Actual And Future Market Is:" << endl;
	cout << "|------------------------------------------------------------------------------------|	" << endl;
	cout << "| plant# | coal  | oil  | garbage | uranium  | coil-oil-hybrid  | can power # cites  |" << endl;
	cout << "|------------------------------------------------------------------------------------|	" << endl;
	for (int i = 0; i < 8; i++)
	{

		cout << "|    " << market[i]->getPlantNumber() << "   |   " << market[i]->coalRequired << "   |  " << market[i]->oilRequired << "   |     " << market[i]->garbageRequired << "   |    " << market[i]->uraniumRequired << "     |        " << market[i]->hybridRequired << "         |       " << market[i]->powersCities << "            |" << endl;
	}
	cout << "|------------------------------------------------------------------------------------|	" << endl << endl;
}

void setUp()
{
	// creating a Map
	Map* map = new Map();
	vector<string> houseColors= { "red", "green", "blue", "purple", "orange", "yellow" };
	citiesMap = map; 
	string trash;

	cout << "Please enter number of players: ";
	cin >> numberOfPlayer;
	getline(cin, trash);
	cout << endl;


	if (numberOfPlayer < 2 || numberOfPlayer > 6)
	{
		cout << "error: Please choose between 2-6 players" << endl;
		system("PAUSE");
		exit(0);
	}

	if (!readMapFromFile(map, "data.txt", numberOfPlayer))
	{

		cout << "Error. Map is not connected" << endl;
		system("PAUSE");
		exit(-1);
	}

	cout << "\n\n***SUMMARY CARD FOR " << numberOfPlayer << " PLAYER GAME\n\n";

	cout << "Number of cards to be randomly removed from PowerPlant deck after market setup: " << summaryCard[1][numberOfPlayer - 2] << endl;
	cout << "Maximum number of PowerPlants owned by a player: " << summaryCard[2][numberOfPlayer - 2] << endl;
	cout << "Number of connected cities to trigger Step 2: " << summaryCard[3][numberOfPlayer - 2] << endl;
	cout << "Number of connected cities to trigger game end: " << summaryCard[4][numberOfPlayer - 2] << endl;

	cout << "\n\n***AVAILABLE RESOURCES";
	string availRes = ("\nCoal: " + std::to_string(GameBoard::availableCoal) + " | Oil: " + std::to_string(GameBoard::availableOil) + " | Garbage: " + std::to_string(GameBoard::availableGarbage) + " | Uranium: " + std::to_string(GameBoard::availableUranium));
	cout << availRes << "\n\n";

	//Maximum plants a player can hold, depending on the number of players playing. Coming straight from summary card.
	int maximumPlantsPerPlayer = summaryCard[2][numberOfPlayer - 2];
	for (int i = 0; i < numberOfPlayer; i++)
	{
		string name;
		string color;

		cout << "\nPlayer " << i + 1 << " / " << "House " << houseColors[i] << ": Please enter player name: " ;
		getline(cin, name);
		players.push_back(new Player(name, houseColors[i], maximumPlantsPerPlayer));
		cout << endl;
	}

	cout << "\n----PLAYER LIST-----" << endl;
	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << players[i]->getName() << endl;
	}
	cout << "----END----\n" << endl;

	cout << "\n----CITY LIST-----" << endl;

	vector<City*> cities = citiesMap->getCities();
	int numberOfRegions = 0;
	for (int i = 0; i < cities.size(); i++)
	{
		if (i % 7 == 0) {
			cout << "\n-REGION: " << numberOfRegions + 1 << endl;
			numberOfRegions++;
		}
		cout << cities.at(i)->getCityName() << endl;
	}

	cout << "\nTotal Regions = " << numberOfRegions << " and Total Cities = " << cities.size() << endl;
	cout << "----END----\n" << endl;

	string startcity;
	for (int i = 0; i < numberOfPlayer; i++)
	{
		while (true)
		{
			cout << players[i]->getName();
			cout << ": pick a starting city: " << endl;
			getline(cin, startcity);

			City* start_city = citiesMap->getCity(startcity);

			if (start_city != NULL)
			{
				players[i]->placeHouse(start_city);
				break;
			}

			cout << "ERROR INVALID CITY!" << endl;
		}
	}
}

void setUpPowerPlantCards()
{	
	//PowerPlant(int plantNumber, int powersCities, int coalRequired, int oilRequired, int garbageRequired, int uraniumRequired, int hybridRequired)
	
	PowerPlant* pp3 = new PowerPlant(3, 1, 0, 2, 0, 0, 0);
	PowerPlant* pp4 = new PowerPlant(4, 1, 2, 0, 0, 0, 0);
	PowerPlant* pp5 = new PowerPlant(5, 1, 0, 0, 0, 0, 2);
	PowerPlant* pp6 = new PowerPlant(6, 1, 0, 0, 1, 0, 0);
	PowerPlant* pp7 = new PowerPlant(7, 2, 0, 3, 0, 0, 0);
	PowerPlant* pp8 = new PowerPlant(8, 2, 3, 0, 0, 0, 0);
	PowerPlant* pp9 = new PowerPlant(9, 1, 0, 1, 0, 0, 0);
	PowerPlant* pp10 = new PowerPlant(10, 2, 2, 0, 0, 0, 0);

	//placing plants in the powerplant vector
	powerplants.push_back(pp3);
	powerplants.push_back(pp4);
	powerplants.push_back(pp5);
	powerplants.push_back(pp6);
	powerplants.push_back(pp7);
	powerplants.push_back(pp8);
	powerplants.push_back(pp9);
	powerplants.push_back(pp10);

	//placing plants 3-10 in the market
	market.push_back(pp3);
	market.push_back(pp4);
	market.push_back(pp5);
	market.push_back(pp6);
	market.push_back(pp7);
	market.push_back(pp8);
	market.push_back(pp9);
	market.push_back(pp10);

	//CARD NUMBER 0 IS THE PHASE 3/STEP 3 CARD. 
	//for loop creates the powerplant cards only(11 to 43) EXCEPT 13 and pushes them to the deck vector (deck vector created at the top of this file)
	for (int i = 11; i <= 43; i++)
	{
		if (i != 13) {
		PowerPlant* plant = new PowerPlant(i);
		powerplants.push_back(plant);
		deck.push_back(plant);
		}
	}
	//Shuffling the deck
	srand(unsigned(std::time(0))); //C++ random is not truly random and you'd get the same shuffle each time. So we are using the current time as seed to get new shuffle patterns.
	random_shuffle(deck.begin(), deck.end());


	//removing the required number of cards depending on the amount of players playing
	int cardsToRemove = summaryCard[1][numberOfPlayer - 2];
	for (int i=0; i < cardsToRemove; i++){
		deck.pop_back();
	}

	//placing plant 13 at the top which I believe is also the requirement. The windmill one.
	PowerPlant* plant13 = new PowerPlant(13, 2, 0, 0, 0, 0, 0);
	deck.push_back(plant13);
	powerplants.push_back(plant13);

	//placing step3 card at the bottom
	PowerPlant* Step3 = new PowerPlant(0);
	deck.insert(deck.begin(), Step3);

	//just sorting the powerplants vector. Not entirely necessary.
	stable_sort(powerplants.begin(), powerplants.end(), [](const PowerPlant* lhs, const PowerPlant* rhs) { //CHANGE stable_sort TO sort IF YOU ENCOUNTER ANY ISSUES

		return lhs->getPlantNumber() < rhs->getPlantNumber();
	});

	cout << "The Actual Market is ";
	for (int i = 0; i < 4; i++)
	{
		cout << market[i]->getPlantNumber() << " ";
	}
	cout << endl;

	cout << "The Future Market is ";
	for (int i = 4; i < 8; i++)
	{
		cout << market[i]->getPlantNumber() << " ";
	}
	cout << endl;
}

void getBoardStatus(vector<City*> cities) {
	for (int i = 0; i < cities.size(); i++) {
		cout << cities[i]->getCityStatus() << ' ';
	}
}

void printPlayerNetwork(Player* player, vector<City*> cityList) {
	cout << "\nPlayer " + player->getName() + " has in his network:";

	if (player->getHouseColor() == "red") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->redHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (player->getHouseColor() == "blue") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->blueHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (player->getHouseColor() == "green") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->greenHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (player->getHouseColor() == "purple") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->purpleHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (player->getHouseColor() == "orange") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->orangeHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
	if (player->getHouseColor() == "yellow") {
		for (int i = 0; i < cityList.size(); i++) {
			if (cityList[i]->yellowHouse == 1) {
				cout << " " + cityList[i]->getCityName();
			}
		}
	}
}

void printPlayerPlants(Player* player) {
	cout << player->getName() << " owns plants:";
	for (int i = 0; i < powerplants.size(); i++) {
		if (powerplants[i]->getOwner() == player) {
			cout << " " << powerplants[i]->getPlantNumber();
		}
	}
	cout << endl;
}

void printDeck()
{
	cout << "Printing powerplant deck";
	for (int i = 0; i < deck.size(); i++) {
		cout << deck[i]->getPlantNumber() << ' ';
	}

}

//sorts by total houses owned. Ties broken by largest plant owned.
void sortPlayersDescending() {
	stable_sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs) { //CHANGE stable_sort TO sort IF YOU ENCOUNTER ANY ISSUES

		if (lhs->totalHouses == rhs->totalHouses) {
			return lhs->largestPlant > rhs->largestPlant;
		}
		return lhs->totalHouses > rhs->totalHouses;
	});
}

//Same idea as above but reverse. Will be used for phases that require bottom to top turn orders etc.
void sortPlayersAscending() {
	stable_sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs) { //CHANGE stable_sort TO sort IF YOU ENCOUNTER ANY ISSUES

		if (lhs->totalHouses == rhs->totalHouses) {
			return lhs->largestPlant < rhs->largestPlant;
		}
		return lhs->totalHouses < rhs->totalHouses;
	});
}

//Sorts market (future/actual)
void sortMarket() {
	stable_sort(market.begin(), market.end(), [](const PowerPlant* lhs, const PowerPlant* rhs) { //CHANGE stable_sort TO sort IF YOU ENCOUNTER ANY ISSUES

		return lhs->getPlantNumber() < rhs->getPlantNumber();
	});
}

GameBoard::GameBoard()
{
	setUp();
}
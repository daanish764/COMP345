#include<iostream>
#include <ctime>
#include<stdlib.h>
#include<map>
#include<algorithm>
#include<fstream>
#include<sstream>

#include<vector>
#include"Player.h"
#include"Map.h"
#include"GameBoard.h"
#include"PowerPlant.h"
#include"OverviewCard.h"

using std::cout;
using std::endl;
using std::cin;

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

//Vector for the overview cards

vector<OverviewCard*> overviewCards;

// Vector for all powerplants
vector<PowerPlant*> powerplants;

// number of Players playing the game
int numberOfPlayer = 0;

// the connected map with all the cities 
Map* citiesMap;

int step2 = 0;
int step3 = 0;

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

//Replenishment rates for each resource
//step(depth) X players(width)
const int coalReplenish[3][5] = { {3, 4, 5, 5, 7},
									{4, 5, 6, 7, 9},
									{3, 3, 4, 5, 6}
};

//step(depth) X players(width)
const int oilReplenish[3][5] = { {2,2,3,4,5},
									{2,3,4,5,6},
									{4,4,4,6,7}
};

//step(depth) X players(width)
const int garbageReplenish[3][5] = { {1,1,2,3,3},
									{2,2,3,3,5},
									{3,3,4,5,6}
};

//step(depth) X players(width)
const int uraniumReplenish[3][5] = { {1,1,1,2,2},
									{1,1,2,3,3},
									{1,1,2,2,3}
};


// the resupply for the number of cities in the bureaucracy phase 
const int resupply[21] = 
{
	10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 119, 134, 138, 142, 145, 148, 150
};


void setUpPowerPlantCards();
int getPowerPlant(int x);
void getBoardStatus(vector<City*> cities);
void printPlayerNetwork(Player* player, vector<City*> cityList);
void printDeck();
void sortPlayersDescending();
void sortPlayersAscending();
void sortMarket();
void sortWinners();

bool GameBoard::gameWinCondition() {
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->getOwnedCities().size() >= summaryCard[4][numberOfPlayer - 2]) {
			step2 = 1;
			cout << "\n\n****************\nGAME ENDED!\n****************\n\n";
			sortWinners();
			cout << "\n\nTHE STANDING AT THE END IS:\n";
			for (int k = 0; k < players.size(); k++) {
				cout << k + 1 << ": " << players[k]->getName() << " with powered cities: " << players[k]->poweredCities << " and elektro: " << players[k]->elektro << endl;
			}
			return true;
		}
	}
	return false;
}


void printGameStatus() {
	vector<City*> cities = citiesMap->getCities();

	cout << "\n***Lets see what each player owns at this point:\n";
	for (int i = 0; i < players.size(); i++) {
		cout << endl << endl;
		players[i]->getPlayerInfo();

		printPlayerNetwork(players[i], cities);
	}

	cout << "\n\n***AVAILABLE RESOURCES";
	string availRes = ("\nCoal: " + std::to_string(GameBoard::availableCoal) + " | Oil: " + std::to_string(GameBoard::availableOil) + " | Garbage: " + std::to_string(GameBoard::availableGarbage) + " | Uranium: " + std::to_string(GameBoard::availableUranium));
	cout << availRes << "\n\n";
}

//phase3 functions
int getCoalCost();
int getOilCost();
int getGarbageCost();
int getUraniumCost();

void phase4();
vector<City*> getConnectableCities(Map* map, City* city, Player* player);

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

	
	cout << "\n***The Plantdeck has been shuffled, " << summaryCard[1][numberOfPlayer - 2] << " cards have been randomly removed and Step 3 card has been put at the bottom and plant 13 at the top.\n";
}

void GameBoard::part2()
{
	cout << "\n\nPHASE 1: DETERMINING PLAYER ORDER\n*************************************" << endl << endl;

	sortPlayersDescending(); //sorts by total houses owned. Ties broken by largest plant owned.
	cout << "***Players with most houses go first. Ties are broken by largest plant owned. Else the order remains intact." << endl;

	//display new order
	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << (i + 1) << ". " << players[i]->getName() << " with " << players[i]->totalHouses << " house(s). Largest plant owned: " << players[i]->largestPlant << endl;
	}

	cout << "\n\nPHASE 2: AUCTION\n*************************************" << endl;

	int chosenPlant = 0;
	vector<Player*> activeAtAuction = players;

	//WHILE LOOP FOR PEOPLE WHO ARE STILL ACTIVE IN PHASE 2 A.K.A HAVE NOT PASSED OR WON A POWERPLANT YET.
	while (activeAtAuction.size() > 0) {
		cout << endl << endl;
		printMarket();
		cout << "It's " << activeAtAuction[0]->getName() << "'s ("<< activeAtAuction[0]->getElektro() <<" Elektros) turn." << endl;

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
					cout << "It's " << activeBidders[currentBidder]->getName() << "'s (" << activeBidders[currentBidder]->getElektro() << " Elektros) turn to place a bid on plant " << chosenPlant << ". Enter a bid: ";
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

				//assign powerplant owner here at activeBidders[0]. Basically the last active bidder. 
				activeBidders[0]->buyPlant(market[getPowerPlant(chosenPlant)], std::max(chosenPlant, highestBid), summaryCard[2][numberOfPlayer - 2]);
				cout << "Powerplant " << chosenPlant << " bought by " << activeBidders[0]->getName() << " for " << std::max(chosenPlant, highestBid) << " Elektros!" << endl;


				//replacing the won powerplant with the top card of the deck and checking for step 3(powerplant 0) card.
				if (deck[deck.size() - 1]->getPlantNumber() != 0) {
					market[getPowerPlant(chosenPlant)] = deck[deck.size() - 1];
				}
				else {
					//if it's a step 3 card, lets take it out of the deck
					deck.pop_back();

					// then put the card under the step 3 card into the market
					market[getPowerPlant(chosenPlant)] = deck[deck.size() - 1];

					//activate step3 and let the players know
					step3 = 1;
					cout << "\n\n****************\nSTEP 3 ACTIVATED!!\n****************\n\n";
				}

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
	printGameStatus();
	
}

void GameBoard::part3() {
	cout << "\n\nPHASE 3: RESOURCE BUYING\n*************************************" << endl << endl;

	sortPlayersAscending(); //sorts by total houses owned. Ties broken by largest plant owned. But in reverse order than previously done
	cout << "***Players with least houses go first. Ties are broken by largest plant owned. Else the order remains intact." << endl;

	//display new order
	for (int i = 0; i < numberOfPlayer; i++)
	{
		cout << (i + 1) << ". " << players[i]->getName() << " with " << players[i]->totalHouses << " house(s). Largest plant owned: " << players[i]->largestPlant << endl;
	}

	
	for (int i = 0; i < players.size(); i++){
		//Capacity for one player to carry any resource given there powerplants
		int coalCapacity = 0;
		int oilCapacity = 0;
		int garbageCapacity = 0;
		int uraniumCapacity = 0;
		int hybridCapacity = 0;
		
		//The amounts the player is looking to buy
		int coalBuy = 0;
		int oilBuy = 0;
		int garbageBuy = 0;
		int uraniumBuy = 0;

		//Players have a limit to how many plants they can hold. If they dump a plant and it turns out they now own a particular resource more than they can hold, we either dump those excess resources
		//or try to see if we can fit the excess oil or coal into the hybrid plants first.
		int excessCoal = 0;
		int excessOil = 0;
		//For loop goes through player's powerplants to scan each plant's resource capacity and subtracts what they already own to give new capacity. Excess oil and coal are also calculated here.
		for (int k = 0; k < players[i]->ownedPlants.size(); k++) {
			coalCapacity += (players[i]->ownedPlants[k]->coalRequired * 2);
			coalCapacity -= players[i]->getCoal();
			if (coalCapacity < 0) { //if capacity is negative, turn capacity=0 in this case and update the excessCoal int.
				excessCoal += players[i]->coal - coalCapacity;
				coalCapacity = 0;
			}

			oilCapacity += (players[i]->ownedPlants[k]->oilRequired * 2);
			oilCapacity -= players[i]->getOil();
			if (oilCapacity < 0) {
				excessOil += players[i]->oil - oilCapacity;
				oilCapacity = 0;
			}

			garbageCapacity += (players[i]->ownedPlants[k]->garbageRequired * 2);
			garbageCapacity -= players[i]->getGarbage();
			if (garbageCapacity < 0) { //If capacity<what we already have, dump the excess
				players[i]->garbage -= garbageCapacity;
				garbageCapacity = 0;
			}

			uraniumCapacity += (players[i]->ownedPlants[k]->uraniumRequired * 2);
			uraniumCapacity -= players[i]->getUranium();
			if (uraniumCapacity < 0) { //If capacity<what we already have, dump the excess
				players[i]->uranium -= uraniumCapacity;
				uraniumCapacity = 0;
			}

			hybridCapacity += (players[i]->ownedPlants[k]->hybridRequired * 2) - excessOil - excessCoal; //hybrid capacity gets subtracted by any excess oil or coal the player has
			if (hybridCapacity < 0) {
				while (hybridCapacity != 0) { //while we're overcapacity, we dump the excess resources one-by-one in an alternating fashion (if both are excess) until we're not.
					if (excessCoal > 0) {
						players[i]->coal -= 1;
						excessCoal -= 1;
						hybridCapacity++;
					}
					if (excessOil > 0) {
						players[i]->oil -= 1;
						excessOil -= 1;
						hybridCapacity++;
					}
					// if the program enters this IF statement, it means that a hybrid plant was dropped so we didn't have excess oil/coal at the non-hybrid
					// plants. So we dump oil and coal one-by-one and check each time until we're not overcapacity.
					if (excessOil == 0 && excessCoal == 0 && hybridCapacity < 0) {
						//dump one coal, if capacity is good, the while loop will break, else it'll drop one oil and process repeats.
						players[i]->coal -= 1;
						hybridCapacity++;

						players[i]->oil -= 1;
						hybridCapacity++;
					}
				}
			}
		}
		cout << "\n\n" << players[i]->getName() << "'s total storage capacity for each resource given his/her power plants, minus current resources owned:";
		cout << "\nCoal Plant(s) Capacity : " << coalCapacity << endl;
		cout << "Oil Plant(s) Capacity : " << oilCapacity << endl;
		cout << "Garbage Plant(s) Capacity : " << garbageCapacity << endl;
		cout << "Uranium Plant(s) Capacity : " << uraniumCapacity << endl;
		cout << "Hybrid Plant(s) Capacity (Coal/Oil) : " << hybridCapacity << endl;
		cout << endl;


		if(coalCapacity>0 || hybridCapacity>0){
			cout << "\n\nPlease enter the amount of COAL you want to buy (including for Hybrid plants): ";
			cin >> coalBuy;
		}
		coalBuy = std::min((coalCapacity + hybridCapacity), coalBuy); //std::min ensures player doesn't get to input more than what they can hold, coal + hybrid capacity in this case.

		//if the player is buying more coal then there COAL plants can hold, we assume they're buying for the hybrid plant and adjust hybridCapacity.
		if (coalBuy > coalCapacity) {
			hybridCapacity = hybridCapacity - (coalBuy - coalCapacity);
		}

		//we need a while loop to give out the resource one at a time because the price of each resource most likely won't be the same depending on it's availability.
		// the functions getCoalCost() or getOilCost() etc. return current price of the resource given it's availability after 1 is handed out.
		//It's the same for every resource so not commenting the same thing for each.
		while (coalBuy > 0) {
			if (GameBoard::availableCoal == 0) { //Abort transaction if resources aren't available
				cout << "\nOut of resource!\n";
				coalBuy = 0;
			}
			if (players[i]->getElektro() < getCoalCost()) { //Abort transaction if the player can't afford the next resource. I.e. if you can afford 2 but enter 3, you still get 2 before it aborts.
				cout << "\nInsufficient funds!";
				coalBuy = 0;
			}
			cout << "\n Acquired 1 coal for " << getCoalCost() << " Elektros";
			players[i]->assignCoal(1, getCoalCost());
			coalBuy -= 1;
		}

		if(oilCapacity>0 || hybridCapacity > 0){
			cout << "\n\nPlease enter the amount of OIL you want to buy (including for Hybrid plants): ";
			cin >> oilBuy;
		}
		oilBuy = std::min((oilCapacity + hybridCapacity), oilBuy);

		while (oilBuy > 0) {
			if (GameBoard::availableOil == 0) {
				cout << "\nOut of resource!\n";
				oilBuy = 0;
			}
			if (players[i]->getElektro() < getOilCost()) {
				cout << "\nInsufficient funds!";
				oilBuy = 0;
			}
			cout << "\n Acquired 1 oil for " << getOilCost() << " Elektros";
			players[i]->assignOil(1, getOilCost());
			oilBuy -= 1;
		}

		if(garbageCapacity>0){
			cout << "\n\nPlease enter the amount of GARBAGE you want to buy: ";
			cin >> garbageBuy;
		}
		garbageBuy = std::min(garbageCapacity, garbageBuy);

		while (garbageBuy > 0) {
			if (GameBoard::availableGarbage == 0) {
				cout << "\nOut of resource!\n";
				garbageBuy = 0;
			}
			if (players[i]->getElektro() < getGarbageCost()) {
				cout << "\nInsufficient funds!";
				garbageBuy = 0;
			}
			cout << "\n Acquired 1 garbage for " << getGarbageCost() << " Elektros";
			players[i]->assignGarbage(1, getGarbageCost());
			garbageBuy -= 1;
		}

		if(uraniumCapacity>0){
			cout << "\n\nPlease enter the amount of URANIUM you want to buy: ";
			cin >> uraniumBuy;
		}
		uraniumBuy = std::min(uraniumCapacity, uraniumBuy);

		while (uraniumBuy > 0) {
			if (GameBoard::availableUranium == 0) {
				cout << "\nOut of resource!\n";
				uraniumBuy = 0;
			}
			if (players[i]->getElektro() < getUraniumCost()) {
				cout << "\nInsufficient funds!";
				uraniumBuy = 0;
			}
			cout << "\n Acquired 1 uranium for " << getUraniumCost() << " Elektros";
			players[i]->assignUranium(1, getUraniumCost());
			uraniumBuy -= 1;
		}
	}

	//Lets see the possessions all the player own
	printGameStatus();
	

	phase4();
}

void GameBoard::part4()
{
	cout << "--------------------------------------------" << endl;
	cout << "PHASE 5 bureaucracy" << endl;
	cout << "--------------------------------------------" << endl;

	for (int i = 0; i < players.size(); i++)
	{

		Player* currentPlayer = players.at(i);
		cout << currentPlayer->getName() << " it your turn take part in bureaucracy" << endl;
		cout << currentPlayer->getElektro() << " is you elektro balance " << endl;

		int numberOfPowerPlants = currentPlayer->ownedPlants.size();

		bool* plantPowered = new bool[numberOfPowerPlants];
		bool poweringTurn = true;
		int cityPowered = 0;

		while (poweringTurn)
		{
			cout << endl << "Your owned powerplant are listed below " << endl;

			cout << "|-----------------------------------------------------------------------------------------------------|" << endl;
			cout << "|  id | plant# | coal  | oil  | garbage | uranium  | coil-oil-hybrid  | can power # cites  | powered  |" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------|" << endl;
			for (int i = 0; i < currentPlayer->ownedPlants.size(); i++)
			{
				cout << "|  " << i << "  ";
				currentPlayer->ownedPlants.at(i)->printPlantInfo();
				string powered = "";
				if (plantPowered[i] == true)
				{
					powered = "true ";
				}
				else {
					powered = "false";
				}

				cout << "  " << powered << "   |" << endl;
			}
			cout << "|-----------------------------------------------------------------------------------------------------|" << endl << endl;
			cout << endl;

			int coal = currentPlayer->getCoal();
			int oil = currentPlayer->getOil();
			int garbage = currentPlayer->getGarbage();
			int uranium = currentPlayer->getUranium();

			cout << "player " << currentPlayer->getName() << " you have your  resources shown below" << endl;

			printf("%-25s%-20s%-15s%\n", "Coal", "Oil", "Garbage", "Uranium");

			printf("%-25s%-20s%-15s%\n", std::to_string(coal).c_str(), std::to_string(oil).c_str(), ::to_string(garbage).c_str(), ::to_string(uranium).c_str());


			if (coal == 0 && oil == 0 && garbage == 0 && uranium == 0)
			{
				cout << endl << "you do not have enough resources to power anything" << endl;
				cout << "your turn is forfeit " << endl << endl;
				poweringTurn = false;
				break;
			}


			cout << endl;
			int plantid;
			cout << "please enter the plant id of the plant you wish to power (-1 to skip phase) > ";
			cin >> plantid;

			if (plantid == -1)
			{
				cout << "you have chosen not to power anything this phase " << endl;
				poweringTurn = false;
				break;
			}

			if (plantid >= currentPlayer->ownedPlants.size())
			{
				cout << "invalid input and you lost your turn " << endl;
				poweringTurn = false;
				break;
			}

			if (plantPowered[plantid] == true)
			{
				cout << "this plant is already powered " << endl;
				cout << "your turn is forfeit " << endl << endl;
				plantPowered = false;
				break;
			}



			PowerPlant* plant = currentPlayer->ownedPlants.at(plantid);

			if (plant->powersCities > currentPlayer->totalHouses)
			{
				cout << "you do not have enough houses to use this card to power cities " << endl;
				cout << "card " << plant->getPlantNumber() << " power " << plant->powersCities << " cities " << endl;
				cout << "You only have " << currentPlayer->totalHouses << endl;
				poweringTurn = false;
				break;
			}

			cout << endl;
			cout << "you selected plant # " << plant->getPlantNumber() << endl;

			if (plant->power(coal, oil, garbage, uranium))
			{
				cout << "you are successfully able to power plant # " << plant->getPlantNumber() << endl << endl;
				players[i]->poweredCities++;

				// getting the required resources of the card
				int coalRequired = plant->coalRequired;
				int oilRequired = plant->oilRequired;
				int garbageRequired = plant->garbageRequired;
				int uraniumRequired = plant->uraniumRequired;
				int hybirdRequired = plant->hybridRequired;

				coal = coal - coalRequired;
				oil = oil - oilRequired;
				garbage = garbage - garbageRequired;
				uranium = uranium - uraniumRequired;

				coal = coal - hybirdRequired / 2;
				oil = oil - hybirdRequired / 2;


				// removing resources of the player 
				currentPlayer->coal = coal;
				currentPlayer->oil = oil;
				currentPlayer->garbage = garbage;
				currentPlayer->uranium = uranium;

				// making sure this powerplant cannot be powered again 
				plantPowered[plantid] = true;

				cout << "player " << currentPlayer->getName() << " your updated are resources shown below" << endl;

				printf("%-25s%-20s%-15s\n", "Coal", "Oil", "Garbage", "Uranium");

				printf("%-25s%-20s%-15s\n", std::to_string(coal).c_str(), std::to_string(oil).c_str(), ::to_string(garbage).c_str(), ::to_string(uranium).c_str());
				cout << endl;



				cityPowered += plant->powersCities;
				cout << "at this point you have the ability to power " << cityPowered << " city."<< endl;

				int input;
				cout << "would you like to select another powerplant to power (1 for yes and 0 for no) > ";
				cin >> input;
				cout << endl;
				if (input == 1)
				{
					poweringTurn = true;
					cout << endl;
				}
				else {
					poweringTurn = false;
					break;
				}
			}
			else
			{
				cout << "you were not able to power power plant # " << plant->getPlantNumber() << endl;
			}

		}

		if (cityPowered > 0)
		{
			cout << "You have the ability to power " << cityPowered << " cities. "<< endl;

			int elektro = 0;
			
			elektro += resupply[cityPowered];
			
			cout << "You have recieved " << resupply[cityPowered] << " elektro " << endl;

			currentPlayer->assignElektro(elektro);

			cout << currentPlayer->getName() << ", your new balance is " << currentPlayer->getElektro() << endl << endl;

		}
	}
	//checking if Step 2 needs to be activated
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->getOwnedCities().size() >= summaryCard[3][numberOfPlayer-2]) {
			step2 = 1;
			cout << "\n\n****************\nSTEP 2 ACTIVATED!!\n****************\n\n";
		}
	}

	//Resource replenishment depending on the phase 
	if (step3 == 1) {
		GameBoard::availableCoal += coalReplenish[2][numberOfPlayer - 2];
		GameBoard::availableOil += oilReplenish[2][numberOfPlayer - 2];
		GameBoard::availableGarbage += garbageReplenish[2][numberOfPlayer - 2];
		GameBoard::availableUranium += uraniumReplenish[2][numberOfPlayer - 2];
	}
	else if (step2 == 1) {
		GameBoard::availableCoal += coalReplenish[1][numberOfPlayer - 2];
		GameBoard::availableOil += oilReplenish[1][numberOfPlayer - 2];
		GameBoard::availableGarbage += garbageReplenish[1][numberOfPlayer - 2];
		GameBoard::availableUranium += uraniumReplenish[1][numberOfPlayer - 2];
	}
	else {
		GameBoard::availableCoal += coalReplenish[0][numberOfPlayer - 2];
		GameBoard::availableOil += oilReplenish[0][numberOfPlayer - 2];
		GameBoard::availableGarbage += garbageReplenish[0][numberOfPlayer - 2];
		GameBoard::availableUranium += uraniumReplenish[0][numberOfPlayer - 2];
	}


	//placing the highest priced plant from the market to the bottom of the deck
	deck.insert(deck.begin(), market[7]);

	//replacing that plant in the market with the top card of the deck
	market[7] = deck[deck.size() - 1];

	//popping that card from the deck
	deck.pop_back();

	//sorting the market again
	sortMarket();

}

void phase4()
{
	cout << "\n\n--------------------------------------------" << endl;
	cout << "phase 4 buidling  " << endl;
	cout << "--------------------------------------------" << endl;

	for (int i = 0; i < players.size(); i++)
	{
		bool pass = false;
		Player* currentPlayer = players.at(i);

		cout << currentPlayer->getName() << " its your turn and " << currentPlayer->getStartCity()->getCityName() << " is your start city" << endl;

		vector<City*> possibleCities = getConnectableCities(citiesMap, currentPlayer->getStartCity(), currentPlayer);

		int connectionCost = 10;
		int city_id;

		cout << "Possible cities you can connect to \n" << endl;
		printf("%-25s%-20s%-15s\n", "City id",  "Name", "cost");
		for (int i = 0; i < possibleCities.size(); i++)
		{
			

			// if there is a house on the city and if there is no house that belongs to be player 
			if (possibleCities.at(i)->getNumberOfHouses() == 1 && possibleCities.at(i)->getNumberOfHouses(currentPlayer->getColor()) == 0)
			{
				
				// different charges based on step
				if (step2 == 1)
				{
					connectionCost = 15;
				}
				else if (step3 == 1)
				{
					connectionCost = 20;
				}
			}

			printf("%-25s%-20s%-15s\n", std::to_string(i).c_str(), possibleCities.at(i)->getCityName().c_str(), std::to_string(connectionCost).c_str());

		}

		if (pass)
			break;
		else {
			cout << "please enter which the city id of the city you would like to build on (-1 to pass ) > ";


			cin >> city_id;
			cout << endl;

			if (city_id == -1)
			{
				cout << currentPlayer->getName() << ", you have chosen to pass.\n" << endl;
				pass = true;
				continue;
			}

			if (city_id >= possibleCities.size())
			{
				cout << "invalid input and you lost you turn to build" << endl;
				pass = true;
				break;
			}
			cout << "you selected " << possibleCities.at(city_id)->getCityName() << endl;

			cout << "you have " << currentPlayer->getElektro() << " elektro at the moment" << endl;

			if (currentPlayer->getElektro() < connectionCost)
			{
				cout << "you do not have enough elektro" << endl;
				break;
			}
			else {
				currentPlayer->subtractElektro(connectionCost);
				possibleCities.at(city_id)->placeHouse(currentPlayer->getColor());
				currentPlayer->totalHouses++;

				cout << "A " << currentPlayer->getColor() << " house was placed on " << possibleCities.at(city_id)->getCityName() << endl;
				currentPlayer->connectToCity(possibleCities.at(city_id));
				cout << currentPlayer->getName() << " your updated balance is " << currentPlayer->getElektro() << " elektro." << endl;
			}
		}

		cout << endl;
	}

	printGameStatus();
}

int getCoalCost() {
	for (int i = 0; i < 8; i++) {
		if (GameBoard::availableCoal >= priceList1[0][i]) {
			return priceList1[1][i];
		}
	}
	return 1000;
}

int getOilCost() {
	for (int i = 0; i < 8; i++) {
		if (GameBoard::availableOil >= priceList1[0][i]) {
			return priceList1[1][i];
		}
	}
	return 1000;
}

int getGarbageCost() {
	for (int i = 0; i < 8; i++) {
		if (GameBoard::availableGarbage >= priceList1[0][i]) {
			return priceList1[1][i];
		}
	}
	return 1000;
}

int getUraniumCost() {
	for (int i = 0; i < 11; i++) {
		if (GameBoard::availableUranium >= priceList2[0][i]) {
			return priceList2[1][i];
		}
	}
	return 1000;
}

vector<City*> getConnectableCities(Map* map, City* city, Player* player)
{


	vector<City*> result;

	if (player->getOwnedCities().size() == 0)
	{
		//cout << player->getName() << "has only no city " << endl;
		//cout << player->getStartCity()->getCityName() << " is pushed to possible cities";
		result.push_back(player->getStartCity());
		return result;
	}
	vector<City*> possibleCities = player->getOwnedCities();

	// loop over all the cities 
	for (std::vector<City*>::iterator it = possibleCities.begin(); it != possibleCities.end(); ++it) 
	{
		City* currentCity = *(it);
		//cout << currentCity->getCityName() << endl;
		
		
			//cout << "found the city " << currentCity->getCityName() << endl;
			// and there is no house on it then we add to possible cities 
			if (currentCity->getNumberOfHouses(player->getColor()) == 0)
			{
				//cout << "if reached ** " << endl;
				//cout << "the city has " << currentCity->getNumberOfHouses(player->getColor()) << " of houses on it " << endl;
				result.push_back(currentCity);
				return result;
			}
			else 
			{
				//cout << "else reached ** " << endl;

				//cout << currentCity->getCityName() << " already has a house on it." << endl;

				// if there is a house on it, 
				
				// loop over all adjacent houses and push only if there is no house on it 
				vector<City*> adjacentCities = currentCity->getAdjacentCities();

				for (int i = 0; i < adjacentCities.size(); i++)
				{
					City* currentAdjCity = adjacentCities.at(i);
					// cout << currentCity->getCityName() << " has an adjacent city " << currentAdjCity->getCityName() << endl;


					//cout << "the city has " << currentAdjCity->getNumberOfHouses(player->getColor()) << " of houses on it " << endl;

					// if there is no house on it 
					if (currentAdjCity->getNumberOfHouses() != 0)
					{

					}
					else {
						if (!player->isConnectedToCity(currentAdjCity))
						{

							result.push_back(currentAdjCity);
							// cout << "putting adjacent city " << currentAdjCity->getCityName() << endl;
						}

					}						
					
				}

			}
		
	}
	return result;
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
		string zero;
		if (market[i]->getPlantNumber() < 10) { 
			zero = "0";
		}
		else {
			zero = "";
		}
		cout << "|   " << zero << market[i]->getPlantNumber() << "   |   " << market[i]->coalRequired << "   |  " << market[i]->oilRequired << "   |     " << market[i]->garbageRequired << "   |    " << market[i]->uraniumRequired << "     |        " << market[i]->hybridRequired << "         |       " << market[i]->powersCities << "            |" << endl;
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
		OverviewCard* newCard = new OverviewCard(i);
		newCard->setOwner(players[i]);
		overviewCards.push_back(newCard);
		cout << players[i]->getName() <<" - Overview Card handed to player." << endl;
		
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
			cout << " pick a starting city: ";
			getline(cin, startcity);

			City* start_city = citiesMap->getCity(startcity);

			if (start_city != NULL)
			{
				players[i]->setStartCity(start_city);
				// players[i]->placeHouse(start_city);
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

//method to call when game ends so the players vector gets sorted by winning rank
void sortWinners() {
	stable_sort(players.begin(), players.end(), [](const Player* lhs, const Player* rhs) { //CHANGE stable_sort TO sort IF YOU ENCOUNTER ANY ISSUES

		//tiebreaker
		if (lhs->poweredCities == rhs->poweredCities) {
			return lhs->elektro > rhs->elektro;
		}
		return lhs->poweredCities > rhs->poweredCities;
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
	setUpPowerPlantCards();
}
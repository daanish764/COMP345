#pragma once
#include"OverviewCard.h"
#include"Player.h"
#include <iostream>
#include<string>
using namespace std;

class OverviewCard
{
private:

public:
	const string description = "1. DETERMINE PLAYER ORDER.\n"
		"2. BUY POWER PLANT\n"
		"    The best begins.\n"
		"    Per round, each may buy one powerplant\n"
		"3. BUY RAW MATERIALS\n"
		"    The wrost begins\n"
		"    Maximum double input per powerplant.\n"
		"4. BUILDING\n"
		"    The wrost begins\n"
		"5. BUREAUCRACY\n"
		"    Get money\n"
		"    In phase 1 and 2: Place highest powerplant under the stack.\n"
		"    In phase 3: Remove lower powerplant from the game.\n"
		"    Restock Raw Material\n";

	int overviewCardNumber;
	Player* owner;

	OverviewCard();
	~OverviewCard();
	OverviewCard(int num);

	void setOwner(Player* name);
	const Player* getOwner() const;
	void printDescription() const;
};
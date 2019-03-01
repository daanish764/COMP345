#pragma once
#include"OverviewCard.h"
#include"Player.h"
#include <iostream>

class OverviewCard
{
private:
	
public:
	int overviewCardNumber;
	Player* owner;

	OverviewCard();
	OverviewCard(int num);
	
	void setOwner(Player* name);
	Player* getOwner();

};
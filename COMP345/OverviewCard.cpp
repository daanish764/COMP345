#include "OverviewCard.h"
#include "Player.h"
#include <iostream>


OverviewCard::OverviewCard()
{

}

OverviewCard::OverviewCard(int num)
{
	this->overviewCardNumber = num;
}


void OverviewCard::setOwner(Player* name) {
	this->owner = name;
}

Player* OverviewCard::getOwner() {
	return this->owner;
}
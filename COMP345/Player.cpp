#include "Player.h"



Player::Player()
{
	name = "";

}

Player::Player(string playerName)
{
	name = playerName;
}

Player::~Player()
{
}

string Player::getName() const
{
	return name;
}

#pragma once
#include<iostream>
using std::string;

class Player
{
private:
	string name;
	int electro;
	int coal;
	int garbage;
	int oil;
	int uranium;
public:
	Player();
	Player(string name);
	~Player();
	string getName() const;
	int getElectro();
	void setElectro(int electro);
	int getCoal();
	void setCoal(int coal);
	int getGarbage();
	void setGarbage(int garbage);
	int getOil();
	void setOil(int oil);
	int getUranium();
	void setUranium(int uranium);
	void getInfo();

};


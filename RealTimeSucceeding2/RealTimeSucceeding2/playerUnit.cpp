#include "playerUnit.h"



playerUnit::playerUnit(sf::Color myTeam)
{
	worldPos.x = 200;
	worldPos.y = 200;
	_textureID = "TBase";
	_layer = 2;
	Initialise(_textureID, 0);
	mySprites[0]->scale(2, 2);
	_textureID = "TTurret";
	Initialise(_textureID, 1);
	mySprites[1]->scale(2, 2);
	_myTeam = myTeam;
	mySprites[1]->setColor(myTeam);
	mySprites[0]->setColor(myTeam);
	
	
}


playerUnit::~playerUnit()
{
}

void playerUnit::update()
{
	//mySprites[1]->rotate(20);
	//Move(1, 1);
}

void playerUnit::rotateTurret(int amount)
{
	mySprites[1]->setRotation(amount);
}
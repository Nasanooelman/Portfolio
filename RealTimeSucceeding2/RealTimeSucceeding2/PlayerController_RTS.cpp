#include "PlayerController_RTS.h"



PlayerController_RTS::PlayerController_RTS()
{
	_textureID = "UI";
	_layer = 3;
	Initialise(_textureID, 0);
	mySprites[0]->setPosition(500, 500);
}


PlayerController_RTS::~PlayerController_RTS()
{
}

void PlayerController_RTS::update()
{
	
}
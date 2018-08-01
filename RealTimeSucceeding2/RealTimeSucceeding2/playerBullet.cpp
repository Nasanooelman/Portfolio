#include "playerBullet.h"



playerBullet::playerBullet(std::string name, float x, float y, float rot, sf::Color playerColor)
{
	this->owner = name;
	this->worldPos.x = x;
	this->worldPos.y = y;
	this->rotation = rot;
	this->_layer = 1;
	this->lifetime = 24*3;

	_textureID = "shellPart";
	Initialise(_textureID, 0);
	this->mySprites[0]->setColor(playerColor);
}


playerBullet::~playerBullet()
{
}

void playerBullet::update()
{
	lifetime--;

	float x2 = worldPos.x += ((cos(0.017453277777 * rotation)) * speed);
	float y2 = worldPos.y += ((sin(0.017453277777 * rotation)) * speed);

	//this->move(x2, y2);

	//Move(x2, y2);

	setPos(x2,y2);
	rotate(rotation-90);
}
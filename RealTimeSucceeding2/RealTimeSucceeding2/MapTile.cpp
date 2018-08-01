#include "MapTile.h"
#include "SFML\Graphics.hpp"


MapTile::MapTile(int x, int y, int h)
{
	worldPos.x = (float)x;
	worldPos.y = (float)y;
	_textureID = "MapTile";
	myData.Hvalue = h;
	myAnimFrame = 0;
	Initialise(_textureID,0);
	mySprites[0]->setTextureRect(sf::IntRect(0, 0, 32, 32));

}


MapTile::~MapTile()
{
	conUnits.clear();
}

void MapTile::update()
{
}

const tileData MapTile::getData()
{
	return myData;
}

std::vector<MapTile*> MapTile::getNeighbours()
{
	int start = myData.Hvalue;

	std::vector<MapTile*> neighbours;

	return neighbours;

}

bool MapTile::enterTile(RTSUnit* unitToEnter, int unitID, int weight)
{
	conUnits.insert(std::make_pair(unitID, unitToEnter));
	passability += weight;
	IDlist.push_back(unitID);

	return true;
}

bool MapTile::leaveTile(int unitID, int weight)
{
	conUnits.erase(unitID);
	passability = 0;
	for (unsigned int i = 0; i < IDlist.size(); i++)
	{
		if (IDlist[i] == unitID)
		{
			IDlist.erase(IDlist.begin() + i);
		}
	}
	return true;
}

int MapTile::getPassability()
{
	return passability;
}


std::vector<RTSUnit*> MapTile::getUnitsInside()
{
	std::vector<RTSUnit*> temp;

	for (unsigned int i = 0; i < IDlist.size(); i++)
	{
		temp.push_back(conUnits[IDlist[i]]);
	}

	return temp;
}

void MapTile::setVision(float i)
{

	if (i < _bright && checked)
		return;

	if (i <= 0.3)
	{
		foggy = true;
		_bright = (float) 0.3;
	}
	if (i >= 1)
	{
		_bright = 1;
	}
	else
	{
		_bright = i;
	}

	checked = true;
}


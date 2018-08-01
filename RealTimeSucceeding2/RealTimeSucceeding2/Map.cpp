#include "Map.h"
Map *Map::_instance{ nullptr };

Map &Map::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Map;
	}
	return *_instance;
}

Map::Map()
{
	//generateMapThread();
	generateMap();
}


void Map::generateMapThread()
{
	std::thread t1(&Map::generateMap, this);

	t1.join();
}

Map::~Map()
{
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			delete test[y][x];
		}
	}
	test.clear();
}

void Map::generateMap()
{
	int placeLocationY = 0;
	int acc = 0;
	for (int y = 0; y < mapSize.y; y++)
	{
		std::vector<MapTile*> temp_vec;
	
			std::cout << (float)y / 10 << "% done generating map" << std::endl;
		
	
		for (int x = 0; x < mapSize.x; x++)
		{
			acc++;
			int placeLocationX = (int)(x * tileSize.x);
			MapTile* tile = new MapTile(placeLocationX, placeLocationY, acc);
			temp_vec.push_back(tile);
		}
		placeLocationY += (int)tileSize.y;
		test.push_back(temp_vec);
	}
	std::cout << "Map generation is finished" << std::endl;
	ready = true;
	lastQueried = test[0][0];
}

void Map::update(CVector2 data, CVector2 offset)
{
}


std::vector<MapTile*> Map::getRadiusOfMap(MapTile* chosen, int radius)
{

	std::vector<MapTile*> tempList;

	for (int y = 0; y < radius*2; y++)
	{
		for (int x = 0; x < radius*2; x++)
		{
			int checkY = (chosen->getWorldPos().y / 32) - radius + y;
			int checkX = (chosen->getWorldPos().x / 32) - radius + x;

			if (checkX >= 1 && checkY >= 1)
			{
				tempList.push_back(test[checkY][checkX]);
			}
		}
	}

	return tempList;
	
}

MapTile* Map::getTile(int x, int y)
{

	unsigned int screensizeX = x;
	unsigned int screensizeY = y;

	if (screensizeX > _screenSize || x < 0)
		return lastQueried;
	if (screensizeY > _screenSize || y < 0)
		return lastQueried;

	int tileX = (int)(x + _offsetX) / (int)tileSize.x;
	int tileY = (int)(y + _offsetY) / (int)tileSize.y;

	lastQueried = test[tileY][tileX];

	return test[tileY][tileX];

}

MapTile* Map::getTile(CVector2 worldPos)
{
	int a = (int)worldPos.x / (int)tileSize.x;
	int b = (int)worldPos.y / (int)tileSize.x;

	if (b < mapSize.y || b > 0)
	{
		if (a < mapSize.x || a > 0)
			return test[b][a];
	}
	else
	{
		return test[0][0];
	}

	return test[0][0];
}

void Map::SetOffset(int offsetX, int offsetY)
{
	_offsetX = offsetX;
	_offsetY = offsetY;
}


void Map::SetOffset(int offsetX, int offsetY, unsigned int screenSize)
{
	_offsetX = offsetX;
	_offsetY = offsetY;
	_screenSize = screenSize;
}

void Map::DeleteThis()
{
	delete this;
}

std::vector<MapTile*> Map::getNeighbours(MapTile* chosen)
{
	int start = chosen->getData().Hvalue;
	MapTile* tileToAdd;
	CVector2 startpos = chosen->getWorldPos();
	std::vector<MapTile*> neighbours;

	// East Neighbour
	if (chosen->getWorldPos().x + tileSize.x <= (mapSize.x * tileSize.x))
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x + tileSize.x, chosen->getWorldPos().y));
		neighbours.push_back(tileToAdd);
	}
	// West Neighbour
	if (chosen->getWorldPos().x - tileSize.x >= 0)
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x - tileSize.x, chosen->getWorldPos().y));
		neighbours.push_back(tileToAdd);
	}
	// South Neighbour
	if (chosen->getWorldPos().y + tileSize.y <= (mapSize.y * tileSize.y))
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x, chosen->getWorldPos().y + tileSize.y));
		neighbours.push_back(tileToAdd);
	}
	// North Neighbour
	if (chosen->getWorldPos().y - tileSize.y >= 0)
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x, chosen->getWorldPos().y - tileSize.y));
		neighbours.push_back(tileToAdd);
	}

	return neighbours;
}

std::vector<MapTile*> Map::getNeighbours_diag(MapTile* chosen)
{
	int start = chosen->getData().Hvalue;
	MapTile* tileToAdd;
	CVector2 startpos = chosen->getWorldPos();
	std::vector<MapTile*> neighbours;

	// East Neighbour
	if (chosen->getWorldPos().x + tileSize.x <= (mapSize.x * tileSize.x))
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x + tileSize.x, chosen->getWorldPos().y));
		neighbours.push_back(tileToAdd);
	}
	// West Neighbour
	if (chosen->getWorldPos().x - tileSize.x >= 0)
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x - tileSize.x, chosen->getWorldPos().y));
		neighbours.push_back(tileToAdd);
	}
	// South Neighbour
	if (chosen->getWorldPos().y + tileSize.y <= (mapSize.y * tileSize.y))
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x, chosen->getWorldPos().y + tileSize.y));
		neighbours.push_back(tileToAdd);
	}
	// North Neighbour
	if (chosen->getWorldPos().y - tileSize.y >= 0)
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x, chosen->getWorldPos().y - tileSize.y));
		neighbours.push_back(tileToAdd);
	}
	//SE Neighbour
	if (chosen->getWorldPos().y + tileSize.y <= (mapSize.y * tileSize.y) && chosen->getWorldPos().x + tileSize.x <= (mapSize.x * tileSize.x))
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x + tileSize.x, chosen->getWorldPos().y + tileSize.y));
		neighbours.push_back(tileToAdd);
	}
	// NE Neighbour
	if (chosen->getWorldPos().y - tileSize.y >= 0 && chosen->getWorldPos().x + tileSize.x <= (mapSize.x * tileSize.x))
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x + tileSize.x, chosen->getWorldPos().y - tileSize.y));
		neighbours.push_back(tileToAdd);
	}
	// SW Neighbour
	if (chosen->getWorldPos().y + tileSize.y <= (mapSize.y * tileSize.y) && chosen->getWorldPos().x - tileSize.x >= 0)
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x - tileSize.x, chosen->getWorldPos().y + tileSize.y));
		neighbours.push_back(tileToAdd);
	}
	// NW Neighbour
	if (chosen->getWorldPos().y - tileSize.y >= 0 && chosen->getWorldPos().x - tileSize.x >= 0)
	{
		tileToAdd = getTile(CVector2(chosen->getWorldPos().x - tileSize.x, chosen->getWorldPos().y - tileSize.y));
		neighbours.push_back(tileToAdd);
	}

	return neighbours;

	//for(int x = -1; x < 2; x++){
	/*for (int y = -1; y < 2; y++) {
	tileToAdd = getTile(CVector2(chosen->getWorldPos().x + (tileSize.x * x), chosen->getWorldPos().y + (tileSize.y * y));
	neighbours.push_back(tileToAdd);
	}*/

}

MapTile* Map::getClosestToMe(MapTile* me, MapTile* target)
{
	// Need to be right of target
	if (me->getWorldPos().x > target->getWorldPos().x)
	{
		// Need to be above target
		if (me->getWorldPos().y < target->getWorldPos().y)
		{
			// Guard to check we arent going off the world. This shouldnt ever be called but better to be safe.
			if (target->getWorldPos().y - tileSize.y >= 0 && target->getWorldPos().x - tileSize.x >= 0)
			{
				// Return north right tile
				return getTile(CVector2(target->getWorldPos().x + tileSize.x, target->getWorldPos().y - tileSize.y));
			}
		}
		// Need to be below target
		if (me->getWorldPos().y > target->getWorldPos().y)
		{
			// Guard to check we arent going off the world. This shouldnt ever be called but better to be safe.
			if (target->getWorldPos().y + tileSize.y <= (mapSize.y * tileSize.y) && target->getWorldPos().x - tileSize.x >= 0)
			{
				// Return south west tile
				return getTile(CVector2(target->getWorldPos().x + tileSize.x, target->getWorldPos().y + tileSize.y));
			}
		}
		else
		{
			// Dont need to move on Y Axis
			return getTile(CVector2(target->getWorldPos().x + tileSize.x, target->getWorldPos().y));
		}
	}
	// Need to be left of target
	if (me->getWorldPos().x < target->getWorldPos().x)
	{
		// Need to be above
		if (me->getWorldPos().y < target->getWorldPos().y)
		{
			// Guard to check we arent going off the world. This shouldnt ever be called but better to be safe.
			if (target->getWorldPos().y + tileSize.y < (mapSize.y * tileSize.y) && target->getWorldPos().x + tileSize.x <= (mapSize.x * tileSize.x))
			{
				// return north west tile
				return getTile(CVector2(target->getWorldPos().x - tileSize.x, target->getWorldPos().y - tileSize.y));
			}
		}
		// Need to be below
		if (me->getWorldPos().y > target->getWorldPos().y)
		{
			// Guard to check we arent going off the world. This shouldnt ever be called but better to be safe.
			if (target->getWorldPos().y - tileSize.y >= 0 && target->getWorldPos().x + tileSize.x <= (mapSize.x * tileSize.x))
			{
				// return south west tile
				return getTile(CVector2(target->getWorldPos().x - tileSize.x, target->getWorldPos().y + tileSize.y));
			}
		}
		else
		{
			// Dont need to move on Y Axis
			return getTile(CVector2(target->getWorldPos().x - tileSize.x, target->getWorldPos().y));
		}
	}
	// I only need to change my Y
	if (me->getWorldPos().x == target->getWorldPos().x)
	{
		// Need to above
		if (me->getWorldPos().y > target->getWorldPos().y)
		{
			// Guard to check we arent going off the world. This shouldnt ever be called but better to be safe.
			if (target->getWorldPos().y + tileSize.y < (mapSize.y * tileSize.y))
			{
				// return southTile
				return getTile(CVector2(target->getWorldPos().x, target->getWorldPos().y + tileSize.y));
			}
		}
		// Need to go below
		if (me->getWorldPos().y < target->getWorldPos().y)
		{
			// Guard to check we arent going off the world. This shouldnt ever be called but better to be safe.
			if (target->getWorldPos().y - tileSize.y >= 0)
			{
				// return north
				return getTile(CVector2(target->getWorldPos().x, target->getWorldPos().y - tileSize.y));
			}
		}
	}
	return me;
}

void Map::CheckVision(int visionRadius, CVector2 pos)
{
	int Xacc = 0;
	int Yacc = 0;


	getTile(pos)->setVision(1);
	for (int y = 0; y < visionRadius; y++)
	{
		for (int x = 0; x < visionRadius; x++)
		{

			if (pos.x + x*tileSize.x - ((visionRadius * tileSize.x) / 2) < mapSize.x*tileSize.x && pos.x + x*tileSize.x - ((visionRadius * tileSize.x) / 2) > 0)
			{
				if (pos.y + y*tileSize.y - ((visionRadius * tileSize.y) / 2)  < mapSize.y*tileSize.y && pos.y + y*tileSize.y - ((visionRadius * tileSize.y) / 2) > 0)
				{
					float circle = ((visionRadius*tileSize.x)*(float)3.14);
					Xacc++;
					// WORKING ON GETTING FOG TO BE A CIRCLE. NOT VERY SUCCESFUL SO FAR.
					/*if (y < (visionRadius / 2))*/

					if (y == 0 || x == 0)
						continue;


					if ((x - y) > (visionRadius / 2))
					{
						continue;
					}
					if ((y - x) > (visionRadius / 2))
					{
						continue;
					}
					if ((y + x) < (visionRadius / 2))
					{
						continue;
					}
					// Find forumula for this one
					if (x == 8 && y == 8 || y == 7 && x == 9 || y == 9 && x == 9 || y == 8 && x == 9 || y == 9 && x == 7 || y == 9 && x == 8)
					{
						continue;
					}




					float BVx = 1 - abs((visionRadius / 2) - x) * (float)0.10;
					float BVy = 1 - abs(y - (visionRadius / 2)) * (float)0.10;






					/*	float BVx = 1- abs(MAP.getTile(pos)->getWorldPos().x - pos.x)*0.10;
					float BVy = 1- abs(MAP.getTile(pos)->getWorldPos().y - pos.y)*0.10;*/


					getTile(CVector2(pos.x + x*tileSize.x - ((visionRadius * tileSize.x) / 2) + 15, pos.y + y*tileSize.y - ((visionRadius * tileSize.y) / 2) + 15))->setVision(std::min(BVx, BVy));
				}
			}
		}
		Yacc++;
		Xacc = 0;
	}

	//Y += MAP.getTileSize().y;
	Xacc = 0;

	//for (int y = 0; y < visionRadius; y++)
	//{
	//	for (int x = 0; x < visionRadius; x++)
	//	{
	//				getTile(CVector2(tilesToUnfog.x += X, tilesToUnfog.y))->setVision(0);
	//				X += MAP.getTileSize().x;
	//		}
	//	X = 0;
	//}

}

// -MAP.getMapSize().x*(visionRadius / 2)
//MAP.getMapSize().y*(visionRadius/2))

void Map::setFog()
{
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			test[y][x]->setVision((float)0.3);
			test[y][x]->checked = false;
		}
	}
}
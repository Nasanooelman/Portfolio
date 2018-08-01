#include "RTSUnit.h"


RTSUnit::RTSUnit()
{
	_textureID = 11;
	worldPos.x = 64;
	worldPos.y = 64;
	_vision = 10;
}

RTSUnit::RTSUnit(int UnitID)
{
	_textureID = "test";
	worldPos.x = 100;
	worldPos.y = 100;
	_unitID = UnitID;
	Initialise(_textureID, 0);
}

RTSUnit::~RTSUnit()
{
}



void RTSUnit::allowedToMove()
{
	if (!initMoveDone)
	{
		myContainer = MAP.getTile(worldPos);
		if (!myContainer->enterTile(this, _unitID, weight))
		{
			return;
		}
	}
	initMoveDone = true;
}


void RTSUnit::MoveToTile(MapTile* dest)
{
	if (dest != _destination || _destination == nullptr)
	{
		_destination = dest;
	}
}

void RTSUnit::move()
{

	if (moveClock == timeToMove)
	{
		moveClock = 0;
	}
	else
	{
		moveClock++;
		return;
	}

	CVector2 desPos = _path[TileToMove]->getWorldPos();

	if (worldPos.x != desPos.x || worldPos.x != desPos.x)
	{
		if (desPos.x > worldPos.x)
		{
			worldPos.x += moveSpeed;
		}

		if (desPos.x < worldPos.x)
		{
			worldPos.x -= moveSpeed;
		}
	}


	if (worldPos.y != desPos.y || worldPos.y != desPos.y)
	{
		if (desPos.y > worldPos.y)
		{
			worldPos.y += moveSpeed;
		}

		if (desPos.y < worldPos.y)
		{
			worldPos.y -= moveSpeed;
		}
	}

	if (worldPos.y == desPos.y && worldPos.x == desPos.x)
	{
		if (TileToMove == _path.size() - 1)
		{
			myContainer->leaveTile(_unitID, weight);
			_path[TileToMove]->enterTile(this, _unitID, weight);
			TileToMove = 0;
			_path.clear();
		}
		else
		{

			myContainer->leaveTile(_unitID, weight);
			myContainer = _path[TileToMove];
			_path[TileToMove]->enterTile(this, _unitID, weight);
			TileToMove++;

		}

	}

}



void RTSUnit::update()
{
	//CVector2 data = CVector2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().x);

	if (_unitID > 0)
	{
		allowedToMove();
	}
	if (!_path.empty())
	{
		move();
	}
}

void RTSUnit::SetDestination(CVector2 data)
{
	if (!_path.empty())
	{
		_path.clear();
		TileToMove = 0;
	}

	pathfind(MAP.getTile(data));
}

void RTSUnit::interaction(CVector2 _mdata)
{

}


void RTSUnit::pathfind(MapTile* dest)
{

	std::vector<MapTile*> newPath;

	// where we are comming
	MapTile* source = MAP.getTile(worldPos);
	MapTile* target = nullptr;

	if (dest->getPassability() >= 1)
	{
		target = MAP.getClosestToMe(source, dest);
	}
	else
	{
		target = dest;
	}


	// the list of nodes already checked
	std::vector<MapTile*> closedSet;
	// the list of nodes we havent checked
	std::vector<MapTile*> openSet;
	openSet.push_back(source);

	std::map<MapTile*, MapTile*> cameFrom;
	std::map<MapTile*, float> gScore;
	std::map<MapTile*, float> fScore;

	// initialise
	for (int y = 0; y < MAP.getMapSize().y; y++)
	{
		for (int x = 0; x < MAP.getMapSize().x; x++)
		{

			MapTile* t = MAP.getTile(CVector2((float)y * MAP.getTileSize().y, (float)x * MAP.getTileSize().x));

			if (t != source)
			{
				gScore[t] = std::numeric_limits<float>::infinity();
				gScore[t] = std::numeric_limits<float>::infinity();
				cameFrom[t] = nullptr;
			}
		}
	}

	cameFrom[source] = nullptr;
	gScore[source] = 0;
	fScore[source] = source->ManHattanDistance(target);

	// Calculate path from target to the source
	while (!openSet.empty())
	{
		MapTile* current = nullptr;

		for each(MapTile* lowestF in openSet)
		{
			if (lowestF == nullptr)
				continue;

			if (current == nullptr || fScore[lowestF] < fScore[current])
				current = lowestF;
		}

		if (current == target)
			break; // exit while loop

				   // remove it as visited
		openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
		closedSet.push_back(current);



		for each(MapTile* neighbor in MAP.getNeighbours_diag(current))
		{
			if (neighbor == nullptr)
				continue;

			// can allow, ignores the neigbour which is already evaluated
			if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end())
				continue;


			// What is the movement cost 			
			float tentative_gScore = gScore[current] + 10;

			if (current->getPassability() >= 1)
			{
				tentative_gScore += 100000;
			}



			if (!(std::find(openSet.begin(), openSet.end(), neighbor) != openSet.end()))
				openSet.push_back(neighbor);
			else if (tentative_gScore >= gScore[neighbor])
				continue; // This is not a better path to continue


						  // record the path
			cameFrom[neighbor] = current;
			gScore[neighbor] = tentative_gScore;
			fScore[neighbor] = gScore[neighbor] + neighbor->ManHattanDistance(target);
		}

	}


	// If we get here then either we have found the shortest route or we cannot get 
	// to our target.
	if (cameFrom[target] == nullptr)
	{
		// no route
		return;
	}


	// Step through the chain and add it to our path
	MapTile* curr = target;
	while (curr != nullptr)
	{
		newPath.push_back(curr);
		curr = cameFrom[curr];
	}

	// We have a route from our target to our source, so we reverse it
	std::reverse(std::begin(newPath), std::end(newPath));

	_path = newPath;
}


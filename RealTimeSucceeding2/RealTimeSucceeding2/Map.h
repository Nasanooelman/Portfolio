#pragma once
#include "MapTile.h"
#include <thread>

class Map
{
public:
	// gets the instance of the Map.
	static Map& GetInstance();
	// list of tiles
	std::vector<std::vector<MapTile*>> test;
	// update for it
	void update(CVector2 data, CVector2 randomdata);
	// get tile functions.
	MapTile* getTile(int x, int y);
	MapTile* getTile(CVector2 worldPos);
	MapTile* getClosestToMe(MapTile* me, MapTile* target);
	// sets the offset of the camera.
	void Map::SetOffset(int offsetX, int offsetY, unsigned int screenSize);
	void Map::SetOffset(int offsetX, int offsetY);
	// deletes this when it is no longer needed.
	void Map::DeleteThis();
	// gets the size of map
	CVector2 const getMapSize() { return mapSize; }
	// get the size of tile
	CVector2 const getTileSize() { return tileSize; }
	// gets the nearest neighbour
	std::vector<MapTile*> getNeighbours(MapTile* chosen);
	// gets the nearest neighbour including diagonals. Mostly for testing purposes
	std::vector<MapTile*> getNeighbours_diag(MapTile* chosen);
	void CheckVision(int visionRadius, CVector2 tilesToUnfog);
	void setFog();
	std::vector<MapTile*> getRadiusOfMap(MapTile* tile, int radius);
	void generateMapThread();
	bool ready = false;
private:
	void generateMap();

	CVector2 mapSize{ 100, 100 };
	CVector2 tileSize{ 32, 32 };
	MapTile* lastQueried;
	static Map* _instance;
	int _offsetY;
	int _offsetX;
	unsigned int _screenSize;
	Map();
	~Map();

};

#define MAP Map::GetInstance()
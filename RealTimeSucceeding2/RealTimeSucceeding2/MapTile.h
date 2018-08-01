#pragma once
#include "GameObject.h"
#include <map>

struct tileData
{
	int movementCost{ 0 };
	int Hvalue{ 0 };
};

class RTSUnit;

class MapTile :
	public GameObject
{
public:
	MapTile(int x, int y, int h);
	~MapTile();
	void update() override;
	const tileData getData();
	float ManHattanDistance(MapTile *nodeEnd)
	{
		float x = (float)(fabs((float)(this->worldPos.x - nodeEnd->getWorldPos().x)));
		float y = (float)(fabs((float)(this->worldPos.y - nodeEnd->getWorldPos().y)));

		return x + y;
	}
	std::vector<MapTile*> getNeighbours();
	bool enterTile(RTSUnit* unitToEnter, int unitID, int weight);
	bool leaveTile(int unitID, int weight);
	std::map <int, RTSUnit* > conUnits;
	std::vector<RTSUnit*> getUnitsInside();
	std::vector<int> IDlist;
	int getPassability();
	void setVision(float i);
	bool foggy = false;
	bool checked = false;
private:
	int passability = 0;
	bool visible;
	tileData myData;
	int number = 0;
	std::string _textureID = "MapTile";
};


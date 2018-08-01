#pragma once
#include "GameObject.h"
#include "Map.h"
#include <map>
#include <vector>

class RTSUnit :
	public GameObject
{
public:
	RTSUnit();
	RTSUnit(int unitID);
	~RTSUnit();
	void update() override;
	void pathfind(MapTile*);
	void MoveToTile(MapTile*);
	int GetWeight() { return weight; }
	void allowedToMove();
	void SetDestination(CVector2 data);
	bool doesItMove = true;
	CVector2 getRallypoint() { return rallyPoint; }
	virtual void interaction(CVector2 _mdata);
	// To:Do Set this to private add getter and setter
	std::string getUnitName() { return unitName; }
private:
	MapTile* _destination = nullptr;
	std::vector<MapTile*> _path;
	MapTile* myContainer;
	int TileToMove = NULL;
	void move();
	int weight = 1;
	bool initMoveDone = false;
	int moveSpeed = 32;
	int timeToMove = 6;
	int moveClock = 0;
protected:
	CVector2 rallyPoint = CVector2(0, 0);
	std::string unitName = "Base_class";
};


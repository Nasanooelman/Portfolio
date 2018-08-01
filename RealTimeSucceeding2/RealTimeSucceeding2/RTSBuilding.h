#pragma once
#include "GameObject.h"
#include "Map.h"
#include "BuildingPiece.h"
class RTSBuilding :
	public GameObject
{
public:
	RTSBuilding();
	~RTSBuilding();
	void update() override;
	void updateResources(int r) override;
	void updateResources(CVector2 rally);
	void interacted(CVector2 _mdata) override;
	void interacted() override;
private:
	std::vector<BuildingPiece*> myFillers;
	void initBuilding();
	bool initted = false;
	CVector2 RallyPoint = CVector2(0, 0);
	bool working = false;
	int workingTime = 2;
	int clock = 0;
	CVector2 _buildingSize = CVector2(6, 6);
	std::string BuildState = "PlaceState";
};


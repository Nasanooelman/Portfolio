#pragma once
#include "RTSUnit.h"
class BuildingPiece :
	public RTSUnit
{
public:
	BuildingPiece(GameObject* myRelay, int RelayID);
	~BuildingPiece();
	void interaction(CVector2 _mdata) override;
	void updateResources(int r) override;
	CVector2 movePoint;
	CVector2 setRelay(CVector2 pos);
	void interacted() override;
private:
	GameObject* _myRelay;
	int _relayID = 0;
};


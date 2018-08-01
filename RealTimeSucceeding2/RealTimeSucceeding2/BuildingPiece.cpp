#include "BuildingPiece.h"



BuildingPiece::BuildingPiece(GameObject* myRelay, int RelayID)
{
	_myRelay = myRelay;
	_mana = NULL;
	_relayID = RelayID;
	_unitID = RelayID;
	doesItMove = false;
	movePoint = CVector2(0, 0);
	unitName = "BaseWithRally";
	_vision = 10;
}


BuildingPiece::~BuildingPiece()
{
}

void BuildingPiece::interaction(CVector2 _mdata)
{
	MESSAGE.sendMessage("INTERACTED", _myRelay, _relayID);
}

void BuildingPiece::updateResources(int r)
{
	_otherResource = r;
}

CVector2 BuildingPiece::setRelay(CVector2 pos)
{
	rallyPoint = pos;
	return movePoint;
}

void BuildingPiece::interacted()
{
	_myRelay->interacted();
}
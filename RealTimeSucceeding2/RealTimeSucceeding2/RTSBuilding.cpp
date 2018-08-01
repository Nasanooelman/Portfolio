#include "RTSBuilding.h"



RTSBuilding::RTSBuilding()
{
	worldPos.x = 256;
	worldPos.y = 256;
}


RTSBuilding::~RTSBuilding()
{
	for (unsigned int i = 0; i < myFillers.size(); i++)
	{
		delete myFillers[i];
	}
	myFillers.clear();
}

void RTSBuilding::update()
{
	initBuilding();

	if (BuildState == "PlaceState")
	{

	}
}

void RTSBuilding::initBuilding()
{
	if (!initted)
	{/*
	 std::vector<C_Tile*> initTile = MAP.getNeighbours_diag(MAP.getTile(CVector2(worldPos.x + MAP.getTileSize().x, worldPos.y + MAP.getTileSize().y)));

	 BuildingPiece* filler = new BuildingPiece(this, _unitID);
	 myFillers.push_back(filler);
	 MAP.getTile(CVector2(worldPos.x + MAP.getTileSize().x, worldPos.y + MAP.getTileSize().y))->enterTile(filler, _unitID, 5);

	 for each(C_Tile* tileToInit in initTile)
	 {
	 BuildingPiece* filler = new FillerUnit(this,_unitID);
	 myFillers.push_back(filler);
	 tileToInit->enterTile(filler, _unitID, 5);
	 }*/

		int Xacc = 0;
		int Yacc = 0;
		for (int y = 0; y < _buildingSize.y; y++)
		{
			for (int x = 0; x < _buildingSize.x; x++)
			{
				BuildingPiece *filler = new BuildingPiece(this, _unitID);
				myFillers.push_back(filler);

				MAP.getTile(CVector2(worldPos.x + Xacc, worldPos.y + Yacc))->enterTile(filler, _unitID, 5);

				Xacc += (int)MAP.getTileSize().x;
			}
			Yacc += (int)MAP.getTileSize().y;
			Xacc = 0;
		}

		//MESSAGE.sendMessage("SPAWN:WORKER", this, RallyPoint);
		initted = true;
	}

	if (working)
	{
		if (clock >= workingTime)
		{
			_otherResource++;
			for each(BuildingPiece *fillers in myFillers)
			{
				fillers->updateResources(_otherResource);
			}
			clock = 0;
		}
		else
		{
			clock++;
		}

		if (_otherResource >= 500)
		{
			_otherResource = 0;
			for each(BuildingPiece *fillers in myFillers)
			{
				fillers->updateResources(_otherResource);
			}
			MESSAGE.sendMessage("SPAWN:WORKER", this, RallyPoint);
			working = false;
		}
	}


}

void RTSBuilding::updateResources(int r)
{
	for (unsigned int i = 0; i < myFillers.size(); i++)
	{
		myFillers[i]->updateResources(r);
	}
}

void RTSBuilding::updateResources(CVector2 rally)
{
	RallyPoint = rally;
}

void RTSBuilding::interacted(CVector2 _mdata)
{
	RallyPoint = MAP.getTile(_mdata)->getWorldPos();

	for each(BuildingPiece *fillers in myFillers)
	{
		fillers->setRelay(RallyPoint);
	}
}

void RTSBuilding::interacted()
{
	if (working)
		return;
	else
	{
		working = true;
	}
}

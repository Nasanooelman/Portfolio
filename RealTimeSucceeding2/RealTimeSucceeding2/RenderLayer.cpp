#include "RenderLayer.h"



RenderLayer::RenderLayer()
{
}


RenderLayer::~RenderLayer()
{
	_OnMyLayer.clear();
}

void RenderLayer::AddUnitsToLayer(GameObject* entity)
{
	_OnMyLayer.push_back(entity);
}


void RenderLayer::RemoveUnitsFromLayer(GameObject* toDelete)
{
	for (unsigned int i = 0; i < _OnMyLayer.size(); i++)
	{
		if (toDelete == _OnMyLayer[i])
		{
			_OnMyLayer.erase(_OnMyLayer.begin() + i);
			return;
		}
	}

	_OnMyLayer.shrink_to_fit();
}

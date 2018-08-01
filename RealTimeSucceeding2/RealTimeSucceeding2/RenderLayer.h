#pragma once
#include <vector>

class GameObject;

class RenderLayer
{
public:
	RenderLayer();
	~RenderLayer();
	const std::vector<GameObject*> GetMyUnits() { return _OnMyLayer; }
	// adds units to the layer
	void AddUnitsToLayer(GameObject*);
	// removes units from the layer
	void RemoveUnitsFromLayer(GameObject*);
private:
	// Units on this render layer
	std::vector<GameObject*> _OnMyLayer;
};


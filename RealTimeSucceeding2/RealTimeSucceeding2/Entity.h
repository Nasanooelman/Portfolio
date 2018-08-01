#include "GameObject.h"
#pragma once
class Entity : public GameObject
{
public:
	Entity();
	~Entity();
	void update();
private:
	int _hunger;
	int _intel;
	int _fitness;
};


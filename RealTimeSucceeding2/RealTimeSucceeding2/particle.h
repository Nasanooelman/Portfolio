#pragma once
#include "GameObject.h"
class particle :
	public GameObject
{
public:
	particle(std::string name, float x, float y, float rot);
	particle();
	~particle();

protected:
	std::string owner = "";
	float rotation = 0;
public:
	int lifetime = 0;
};


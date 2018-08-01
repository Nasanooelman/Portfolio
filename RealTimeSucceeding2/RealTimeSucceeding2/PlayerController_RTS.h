#pragma once
#include "GameObject.h"
class PlayerController_RTS :
	public GameObject
{
public:
	PlayerController_RTS();
	~PlayerController_RTS();
	void update() override;
};


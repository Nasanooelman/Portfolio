#pragma once
#include "Entity.h"
class playerUnit :
	public Entity
{
public:
	playerUnit(sf::Color myTeam);
	~playerUnit();
	void update() override;
	void rotateTurret(int amount);
	sf::Color _myTeam = sf::Color(255, 0, 102, 255);
};


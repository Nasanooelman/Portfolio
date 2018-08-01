#pragma once
#include "particle.h"
class playerBullet :
	public particle
{
public:
	playerBullet(std::string name, float x, float y, float rot, sf::Color playerColor);
	~playerBullet();
	void update() override;
	float speed = 10;
};


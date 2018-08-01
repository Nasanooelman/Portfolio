#pragma once
#include "GameWorld.h"

class GameState
{
public:
	GameState();
	~GameState();
	void updateState(sf::RenderWindow* window);
	void addToWorld(GameObject*);
private:
	GameWorld* _World = new GameWorld;
};


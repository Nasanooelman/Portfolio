#pragma once
#include "viz.h"
#include "Map.h"
#include "RenderLayer.h"
#include "MessageSystem.h"
#include "RTSUnit.h"
#include "PlayerController_RTS.h"
#include "playerUnit.h"
#include "playerBullet.h"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	// Updates all entities in the world and the world itself.
	void Update(sf::RenderWindow* window);
	void AddToWorld(GameObject* entity);
private:
	// List of all objects currently in the world
	std::vector<GameObject*> _worldList;
	// clock for the world
	sf::Clock GameClock;
	// the speed at which the game runs
	sf::Time GameSpeed;
	// Order in which things are rendered
	std::vector<RenderLayer*> _RenderOrder;
	void readMessages();
	void createUnit(CVector2 pos, std::string unitToCreate);
	PlayerController_RTS* player = nullptr;
	RTSUnit* unit = nullptr;
	std::map<std::string, playerUnit*> playerMap;
	bool firstUpdate = true;
	bool cooldown = false;
	int timer = 0;

	float tempRot = 0;
	float tempX = 200;
	float tempY = 200;
	int turretRot = 0;

	playerUnit* testUnit = nullptr;
	RenderLayer* _layer1 = nullptr;
	RenderLayer* _layer2 = nullptr;
	RenderLayer* _layer3 = nullptr;

};


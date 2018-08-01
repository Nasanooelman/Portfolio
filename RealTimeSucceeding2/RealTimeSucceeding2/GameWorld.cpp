#include "GameWorld.h"
#include <cmath>



GameWorld::GameWorld()
{
	// the game will update every 25 miliseconds
	GameSpeed = sf::milliseconds(25);
	// Initialise render layers
	_layer1 = new RenderLayer;
	_layer2 = new RenderLayer;
	_layer3 = new RenderLayer;

	player = new PlayerController_RTS;
	testUnit = new playerUnit(sf::Color(255,0,0,255));
	playerMap["fred"] = testUnit;
	//unit = new RTSUnit;
	//AddToWorld(unit);
	AddToWorld(player);
	AddToWorld(testUnit);
}


GameWorld::~GameWorld()
{
	_worldList.clear();
	delete _layer1;
	delete _layer2;
	delete _layer3;
}

void GameWorld::Update(sf::RenderWindow* window)
{

	if (firstUpdate)
	{
		MAP.generateMapThread();
		firstUpdate = false;
	}
	window->clear();	

	// Updates all entities in the world
	sf::Time elapsed = GameClock.getElapsedTime();

	if (elapsed >= GameSpeed)
	{
		for each(GameObject* entity in _worldList)
		{
			entity->update();
		}

		GameClock.restart();
	}

	// Draws the map. This has to be done here as the map is not part of the world.
	//
	//for (int y = 0; y < 40; y++)
	//{
	//	for (int x = 0; x < 40; x++)
	//	{

	//		window->draw(*MAP.test[y][x]->mySprites[0]);
	//	}
	//}

	if (MAP.ready)
	{
		MapTile* checkTile = MAP.getTile(testUnit->getWorldPos());
		std::vector<MapTile*> tilesToDraw = MAP.getRadiusOfMap(checkTile, 20);

		for (int i = 0; i < tilesToDraw.size(); i++)
		{
			window->draw(*tilesToDraw[i]->mySprites[0]);
		}
	}

	// Draws all the units. units in a lower render layer are drawn first
	for each  (RenderLayer* currentLayer in _RenderOrder)
	{
		std::vector<GameObject*> tempVec = currentLayer->GetMyUnits();
		// Checks to see if there is anything on the layer to render
		if (!tempVec.empty())
		{
			for each (GameObject* entity in tempVec)
			{
				// draws the unit
				for each (sf::Sprite* sprite in entity->mySprites)
				{
					window->draw(*sprite);
				}
				
			}
		}
	}
	// 

	if (sf::Keyboard::isKeyPressed)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			tempRot++;
			/*if (tempRot > 360)
			{
				tempRot = 360;
			}*/

			std::string tempMessage = "playerPos:fred:" + std::to_string(tempRot) + ":";
			tempMessage = tempMessage + std::to_string(tempX) + ":";
			tempMessage = tempMessage + std::to_string(tempY) + ":";
			tempMessage = tempMessage + std::to_string(turretRot);

			std::cout << tempMessage << std::endl;

			MESSAGE.sendMessage(tempMessage, nullptr);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			tempRot--;
		/*	if (tempRot < 0)
			{
				tempRot = 0;
			}*/
			std::string tempMessage = "playerPos:fred:" + std::to_string(tempRot) + ":";
			tempMessage = tempMessage + std::to_string(tempX) + ":";
			tempMessage = tempMessage + std::to_string(tempY) + ":";
			tempMessage = tempMessage + std::to_string(turretRot);

			std::cout << tempMessage << std::endl;

			MESSAGE.sendMessage(tempMessage, nullptr);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			int speedX = 2;
			int speedY = 2;

			tempX += (cos(0.017453277777 * tempRot)) * speedX;
			tempY += (sin(0.017453277777 * tempRot)) * speedY;

			std::string tempMessage = "playerPos:fred:" + std::to_string(tempRot) + ":";
			tempMessage = tempMessage + std::to_string(tempX) + ":";
			tempMessage = tempMessage + std::to_string(tempY) + ":";
			tempMessage = tempMessage + std::to_string(turretRot);

			std::cout << tempMessage << std::endl;

			MESSAGE.sendMessage(tempMessage, nullptr);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			
			int speedX = 2;
			int speedY = 2;

			tempX += (-cos(0.017453277777 * tempRot)) * speedX;
			tempY += (-sin(0.017453277777 * tempRot)) * speedY;

			std::string tempMessage = "playerPos:fred:" + std::to_string(tempRot) + ":";
			tempMessage = tempMessage + std::to_string(tempX) + ":";
			tempMessage = tempMessage + std::to_string(tempY) + ":";
			tempMessage = tempMessage + std::to_string(turretRot);

			std::cout << tempMessage << std::endl;

			MESSAGE.sendMessage(tempMessage, nullptr);


		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			turretRot-=2;
			std::string tempMessage = "playerPos:fred:" + std::to_string(tempRot) + ":";
			tempMessage = tempMessage + std::to_string(tempX) + ":";
			tempMessage = tempMessage + std::to_string(tempY) + ":";
			tempMessage = tempMessage + std::to_string(turretRot);

			std::cout << tempMessage << std::endl;

			MESSAGE.sendMessage(tempMessage, nullptr);



		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			turretRot+=2;
			std::string tempMessage = "playerPos:fred:" + std::to_string(tempRot) + ":";
			tempMessage = tempMessage + std::to_string(tempX) + ":";
			tempMessage = tempMessage + std::to_string(tempY) + ":";
			tempMessage = tempMessage + std::to_string(turretRot);

			std::cout << tempMessage << std::endl;

			MESSAGE.sendMessage(tempMessage, nullptr);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!cooldown)
			{
				timer--;
				if (timer <= 0)
				{
					cooldown = true;
				}
			}
			else
			{
				std::string tempMessage = "playerShoot:fred:" + std::to_string(tempX) + ":";
				tempMessage = tempMessage + std::to_string(tempY) + ":";
				tempMessage = tempMessage + std::to_string(turretRot) + ":";
				std::cout << tempMessage << std::endl;
				MESSAGE.sendMessage(tempMessage, nullptr);
				timer = 12;

				std::cout << tempMessage << std::endl;

				cooldown = false;
			}
		}



	}

		// Reads messages from the units in the world
		readMessages();

		sf::View currentPlayerView;
		player->setPos(tempX, tempY);
		currentPlayerView.setCenter(player->getWorldPos().x, player->getWorldPos().y);
		window->setView(currentPlayerView);
		window->display();
		_worldList.shrink_to_fit();

	
}

void GameWorld::AddToWorld(GameObject* entity)
{
	// adds units to the world
	_worldList.push_back(entity);

	// If the object is to be rendered on a higher render level than we currently have.
	// Increase the render levels till we reach it
	if (_RenderOrder.size() < entity->GetLayer())
	{
		for (int i = 0; _RenderOrder.size() < entity->GetLayer(); i++)
		{
			RenderLayer* layer = new RenderLayer;
			_RenderOrder.push_back(layer);
		}
	}
	// Adds unit to its render level
	if (entity->GetLayer() >= 1)
	{
		_RenderOrder[entity->GetLayer()-1]->AddUnitsToLayer(entity);
	}
	else
	{
		_RenderOrder[entity->GetLayer()]->AddUnitsToLayer(entity);
	}
}

void GameWorld::createUnit(CVector2 pos, std::string unitToCreate)
{
	if (unitToCreate == "WORKER")
	{
		RTSUnit* worker = new RTSUnit;
		worker->setXY(pos);
		AddToWorld(worker);
	}
}

void GameWorld::readMessages()
{
	if (MESSAGE.QueSize() > 0)
	{
		for (unsigned int i = 0; i < MESSAGE.QueSize(); i++)
		{


			std::string str = MESSAGE.getMessage(i)->mess;

			std::vector<std::string> tempList = MESSAGE.split(str, ":");

			// Updates Values in objects
			if (MESSAGE.getMessage(i)->mess == "INTERACTED")
			{
				// To DO make it so you spend gold when you create a unit

				//MESSAGE.getMessage(i)->sender->interacted(mouseData);

			}

			if (MESSAGE.getMessage(i)->mess == "SPAWN:WORKER")
			{
				int messageNumber = i;
				createUnit(MESSAGE.getMessage(i)->sendvalue_Vec, "WORKER");
				//MESSAGE.getMessage(i)->unit_sender->rallyPoint
			}

			if (MESSAGE.getMessage(i)->mess == "DRAW:PARTICLE")
			{
				// I_Target here is used as a shortcut for the ID of the particle we want to draw
				//DRAW.DrawSprite(MESSAGE.getMessage(i)->I_target, inCameraXY(MESSAGE.getMessage(i)->sendvalue_Vec).x, inCameraXY(MESSAGE.getMessage(i)->sendvalue_Vec).y, MESSAGE.getMessage(i)->sender->getFrame());
			}

			if (tempList[0] == "playerPos")
			{
				playerMap[tempList[1]]->rotate(stof(tempList[2]) - 90);
				playerMap[tempList[1]]->setPos(stof(tempList[3]), stof(tempList[4]));
				playerMap[tempList[1]]->rotateTurret(stof(tempList[5]));

			}
			else if (tempList[0] == "playerShoot")
			{
				playerBullet* shell = new playerBullet(tempList[1], stof(tempList[2]), stof(tempList[3]), stof(tempList[4])+90 , testUnit->_myTeam);
				AddToWorld(shell);
			}
		}

		MESSAGE.doneReading();
	}
}
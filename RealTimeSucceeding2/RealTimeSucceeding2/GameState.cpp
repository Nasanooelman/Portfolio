#include "GameState.h"



GameState::GameState()
{
}


GameState::~GameState()
{
	delete _World;
}

void GameState::updateState(sf::RenderWindow* window)
{
	_World->Update(window);
}

void GameState::addToWorld(GameObject* obj)
{
	_World->AddToWorld(obj);
}
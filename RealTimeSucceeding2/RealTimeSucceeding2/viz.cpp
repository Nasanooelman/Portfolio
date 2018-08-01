#include "viz.h"

Visualisation *Visualisation::_instance{ nullptr };

Visualisation &Visualisation::GetInstance()
{
	if (_instance == nullptr)
		_instance = new Visualisation;
	return *_instance;
}



Visualisation::Visualisation()
{
	 //Name    //File Location   //Render Layer
	createTexture("test", "WhiteBlock.png");
	createTexture("MapTile", "otherTile.png");
	createTexture("UI", "ui.png");
	createTexture("TBase", "tankBase.png");
	createTexture("TTurret", "tankTurret.png");
	createTexture("shellPart", "shell.png");
}


Visualisation::~Visualisation()
{
	spriteList.clear();
}

bool Visualisation::createTexture(std::string name, std::string fileLocation)
{
	sf::Texture* spritesTexture = new sf::Texture;
	if (!spritesTexture->loadFromFile(fileLocation))
	{
		return false;
	}

	spriteList.insert(std::make_pair(name, spritesTexture));

	return true;
}


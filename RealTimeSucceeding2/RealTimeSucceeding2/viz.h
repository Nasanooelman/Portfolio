#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class Visualisation
{
public:
	static Visualisation& GetInstance();
	sf::Texture &getTex(std::string spriteName) { return *spriteList[spriteName]; }
	void DeleteThis() { delete this; }
	
private:
	Visualisation();
	~Visualisation();
	static Visualisation* _instance;
	// Creates a sprite with a texture and adds the list of drawable sprites
	bool createTexture(std::string name, std::string fileLocation);
	
	std::map <std::string, sf::Texture*> spriteList;
};

#define DRAW Visualisation::GetInstance()
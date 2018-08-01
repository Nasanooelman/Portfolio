#pragma once
#include "vec2.h"
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include "MessageSystem.h"


struct animations
{
	int frameStart;
	int frameLast;
	int animLength;
	std::string name;

};

class GameObject
{
public:
	GameObject();
	~GameObject();

	
	// gets the world position vector
	CVector2 getWorldPos();
	// gets the texture ID
	std::string getTexture();
	// update function that is called by the world
	virtual void update();
	// plays a specific animation
	void playAnimation(std::string name);
	// adds an animation the list
	void addAnimation(int f_start, int a_length, std::string name, int f_last);
	// returns the current frame
	int getFrame();
	// moves it to the next frame
	void nextFrame();
	// To:do
	bool playing();
	// sets the object to a specific sprite in it's animation
	void setFrame(int f);
	// gets the ID.
	int ID();
	// Sets and then Gets the ID
	int ID(int IdtoSet);
	// gets health
	int getHealth() { return _health; }
	// gets mana
	int getMana() { return _mana; }
	// This is really bad I don't like having this here
	int getOtherResource() { return _otherResource; }
	// gets vision
	int GetVision() { return _vision; }
	// Sets the world position of this object
	void setXY(CVector2 pos) { worldPos = pos; }
	// returns the brightness of the object. used for lighting
	float getBrightness() { return _bright; }
	//updates a resource for a renderable

	// I think these are obselete now. Not sure.
	virtual void updateResources(int r);
	virtual void updateResources(CVector2 r);
	// Base interaction function. To be called from other classes to do actions.
	virtual void interacted();
	// Base interaction function. To be called from other classes to do actions. Has Mousedata.
	virtual void interacted(CVector2 _mdata);
	
	unsigned int GetLayer() { return _layer; }

	//sf::Sprite* mySprite;

	void rotate(float amount);
	void setPos(int x, int y);
	std::vector<sf::Sprite*> mySprites;


protected:
	float worldRotation = 0;
	// texture assigned to the object
	std::string _textureID = "";
	int _texture_Width;
	int _texture_Height;
	int tickTime = 0;
	// list of animations this entity has
	std::vector<animations> animation_List;
	// the current animation
	animations currentAnimation;
	// animation frame it is currently on.
	int myAnimFrame = 0;
	// if the animation is playing
	bool playingAnim = false;
	// the world position of an object
	CVector2 worldPos = CVector2(0, 0);
	// it's texture ID
	int _unitID;
	// it's health
	int _health = 100;
	// it's mana
	int _mana = 100;
	// it's other resource
	int _otherResource = 0;
	// not sure what the difference is between these
	int _vision = 0;
	float _bright = 1;
	unsigned int _layer = 1;
	void Initialise(std::string text, int layer);
	void Move(int x, int y);

};


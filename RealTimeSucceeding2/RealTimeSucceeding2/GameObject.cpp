#include "GameObject.h"
#include "viz.h"


GameObject::GameObject()
{
	
}


GameObject::~GameObject()
{
}


std::string GameObject::getTexture() {

	return _textureID;

}

CVector2 GameObject::getWorldPos()
{
	return worldPos;
}


// updates the object causing any checks to happen //
void GameObject::update()
{
	for each (sf::Sprite* sprit in mySprites)
	{
		sprit->setPosition(worldPos.x, worldPos.y);
		sprit->setRotation(worldRotation);
	}
	
}

void GameObject::rotate(float amount)
{
	for each (sf::Sprite* sprit in mySprites)
	{
		sprit->setRotation(amount);
	}
}

void GameObject::playAnimation(std::string nameCheck)
{

	for (unsigned int i = 0; i < animation_List.size(); i++)
	{
		if (animation_List[i].name == nameCheck) {

			myAnimFrame = animation_List[i].frameStart;
			currentAnimation = animation_List[i];
			if (!playing()) {

				playingAnim = true;
			}
		}
	}

}

// not tested not sure if you can add to a list and then delete the original
void GameObject::addAnimation(int f_start, int a_length, std::string name, int f_last)
{

	animations newAnim;
	newAnim.animLength = a_length;
	newAnim.frameStart = f_start;
	newAnim.name = name;
	newAnim.frameLast = f_last;

	animation_List.push_back(newAnim);


}

// returns the current frame that the animation is on
int GameObject::getFrame()
{
	return myAnimFrame;
}

// checks if the animation is playing
bool GameObject::playing()
{
	return playingAnim;
}

// sets the frame to the next one
void GameObject::nextFrame()
{

	if (playingAnim)
	{
		// Undefined right now
		if (myAnimFrame == currentAnimation.frameLast)
		{
			myAnimFrame = currentAnimation.frameStart;
		}

		else
		{
			myAnimFrame++;
		}
	}

	if (!playingAnim)
	{
		if (myAnimFrame == currentAnimation.frameLast)
		{
			myAnimFrame = currentAnimation.frameStart;
		}

		myAnimFrame++;
	}


}

void GameObject::setFrame(int f)
{
	myAnimFrame = f;
}


int GameObject::ID()
{
	return _unitID;
}

int GameObject::ID(int IdtoSet)
{
	_unitID = IdtoSet;
	return _unitID;
}


void GameObject::updateResources(int r)
{
}

void GameObject::updateResources(CVector2 r)
{
}

void GameObject::interacted(CVector2 _mdata)
{

}

void GameObject::interacted()
{

}

void GameObject::Initialise(std::string textureID, int layer)
{
	sf::Sprite* sprit = new sf::Sprite;

	mySprites.push_back(sprit);

	mySprites[layer]->setTexture(DRAW.getTex(textureID));
	if (mySprites[layer]->getTexture() == NULL)
		return;
	int x = DRAW.getTex(textureID).getSize().x;
	int y = DRAW.getTex(textureID).getSize().y;
	mySprites[layer]->setPosition(worldPos.x, worldPos.y);

	mySprites[layer]->setOrigin(sf::Vector2f((x / 2), (y / 2)));
}

void GameObject::Move(int x, int y)
{
	worldPos.x += x;
	worldPos.y += y;

	double X = worldPos.x;
	double Y = worldPos.y;
	for (unsigned int i = 0; i < mySprites.size(); i++)
	{
		mySprites[i]->setPosition((float)X, (float)Y);
	}
	
}

void GameObject::setPos(int x, int y)
{
	worldPos.x = x;
	worldPos.y = y;

	double X = x;
	double Y = y;

	for (unsigned int i = 0; i < mySprites.size(); i++)
	{
		mySprites[i]->setPosition((float)X, (float)Y);
	}
}
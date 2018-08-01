#include "particle.h"



particle::particle(std::string name, float x, float y, float rot)
{
	this->owner = name;
	this->worldPos.x = x;
	this->worldPos.y = y;
	this->rotation = rot;
}

particle::particle()
{

}

particle::~particle()
{
}

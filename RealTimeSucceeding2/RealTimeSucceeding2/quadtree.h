#pragma once
#include <list>

class quadtree
{
public:
	quadtree();
	~quadtree();

private:
	int MAX_OBJECTS = 10;
	int MAX_LEVELS = 5;

	int level;
	
};


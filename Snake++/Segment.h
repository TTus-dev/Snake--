#pragma once
#include "GameObject.h"

class Segment : public Game_Object
{
public:
	int direction;
	Segment* next;
	Segment(int dir, int tx, int ty, sf::Image assets[], int texture_id);
};
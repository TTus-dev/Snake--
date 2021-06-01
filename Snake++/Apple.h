#pragma once
#include "GameObject.h"
#include "Snake.h"

class Apple : public Game_Object
{
public:
	Apple(sf::Image assets[]);
	void Apple_gen(Snake* snake);
	void draw_Apple(sf::RenderWindow*);
};
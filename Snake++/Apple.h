#pragma once
#include "GameObject.h"

class Apple : public Game_Object
{
public:
	Apple(sf::Image assets[]);
	void Apple_gen();
	void draw_Apple(sf::RenderWindow* window_ptr);
};
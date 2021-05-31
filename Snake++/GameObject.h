#pragma once
#include <SFML/Graphics.hpp>

class Game_Object
{
public:
    int x, y, spr_id;
    sf::Texture sprite;
    sf::RectangleShape hitbox;
};
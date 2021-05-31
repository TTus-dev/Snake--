#pragma once
#include "Segment.h"
#include "Apple.h"

class Snake
{
public:
    int direction, score;
    Segment* head;
    void set_dir(int x);
    void _update_helper(int prev_dir, Segment* _iter, sf::Image assets[]);
    void update_sprites(bool grow_state, sf::Image assets[]);
    void move(bool grow_state);
    void draw_snake(sf::RenderWindow* window_ptr);
    void grow(sf::Image assets[]);
    bool eat(Apple food);
    void swapper(int* x, int* y);
};
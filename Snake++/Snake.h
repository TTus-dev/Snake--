#pragma once
#include "Segment.h"

class Snake
{
public:
    int direction, score;
    Segment* head;
    void set_dir(int);
    void _update_helper(int prev_dir, Segment* _iter, sf::Image assets[]);
    void update_sprites(bool grow_state, sf::Image assets[]);
    void move(bool grow_state);
    void draw_snake(sf::RenderWindow*);
    void grow(sf::Image asset[]);
    bool eat(int foodx, int foody);
    void swapper(int* swap1, int* swap2);
    bool in_snake(int mode, int x = -1, int y = -1);
};
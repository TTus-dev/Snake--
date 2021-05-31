#include "Snake.h"

void Snake::set_dir(int x)
{
	direction = x;
	head->direction = x;
}

void Snake::_update_helper(int prev_dir, Segment* _iter, sf::Image assets[])
{
    if (prev_dir != _iter->direction) {
        if (prev_dir == 1) {
            if (_iter->direction == 2) { _iter->sprite.loadFromImage(assets[5]); }
            else { _iter->sprite.loadFromImage(assets[4]); }
        }

        else if (prev_dir == 2) {
            if (_iter->direction == 3) { _iter->sprite.loadFromImage(assets[4]); }
            else { _iter->sprite.loadFromImage(assets[6]); }
        }

        else if (prev_dir == 3) {
            if (_iter->direction == 2) { _iter->sprite.loadFromImage(assets[7]); }
            else { _iter->sprite.loadFromImage(assets[6]); }
        }

        else if (prev_dir == 4) {
            if (_iter->direction == 3) { _iter->sprite.loadFromImage(assets[5]); }
            else { _iter->sprite.loadFromImage(assets[7]); }
        }
    }
    else
    {
        if (_iter->direction == 1 || _iter->direction == 3) { _iter->sprite.loadFromImage(assets[13]); }
        else { _iter->sprite.loadFromImage(assets[12]); }
    }
}

void Snake::update_sprites(bool grow_state, sf::Image assets[]) {
    head->sprite.loadFromImage(assets[head->direction - 1]);
    head->hitbox.setTexture(&head->sprite);
    Segment* _iter = head->next;
    int prev_dir = head->direction;
    if (!grow_state) {
        while (_iter->next != NULL) {
            _update_helper(prev_dir, _iter, assets);
            _iter->hitbox.setTexture(&_iter->sprite);
            prev_dir = _iter->direction;
            _iter = _iter->next;
        }
        _iter->sprite.loadFromImage(assets[prev_dir + 7]);
        _iter->hitbox.setTexture(&_iter->sprite);
    }
    else {
        _update_helper(prev_dir, _iter, assets);
        _iter->hitbox.setTexture(&_iter->sprite);
        prev_dir = _iter->direction;
    }
}

void Snake::move(bool grow_state)
{
    int old_x = head->x;
    int old_y = head->y;
    int old_dir = head->direction;
    switch (direction)
    {
    case 1:
        if (head->y > 0) head->y--;
        else head->y = 23;
        break;

    case 2:
        if (head->x < 31) head->x++;
        else head->x = 0;
        break;

    case 3:
        if (head->y < 23) head->y++;
        else head->y = 0;
        break;

    case 4:
        if (head->x > 0) head->x--;
        else head->x = 31;
        break;
    }
    Segment* _iter = head->next;
    if (!grow_state) {
        while (_iter != NULL) {
            swapper(&_iter->x, &old_x);
            swapper(&_iter->y, &old_y);
            swapper(&_iter->direction, &old_dir);
            _iter = _iter->next;
        }
    }
    else {
        swapper(&_iter->x, &old_x);
        swapper(&_iter->y, &old_y);
        swapper(&_iter->direction, &old_dir);
    }
}

void Snake::draw_snake(sf::RenderWindow* window_ptr)
{
    Segment* _tmp = head;
    while (_tmp != NULL) {
        _tmp->hitbox.setPosition(_tmp->x * 25, _tmp->y * 25);
        window_ptr->draw(_tmp->hitbox);
        _tmp = _tmp->next;
    }
}

void Snake::grow(sf::Image assets[])
{
    Segment* _tmp = head->next;
    head->next = new Segment(_tmp->direction, _tmp->x, _tmp->y, assets, _tmp->spr_id);
    head->next->next = _tmp;
}

bool Snake::eat(Apple food)
{
    return food.x == head->x && food.y == head->y;
}

void Snake::swapper(int* x, int* y)
{
    int _tmp;
    _tmp = *x;
    *x = *y;
    *y = _tmp;
}
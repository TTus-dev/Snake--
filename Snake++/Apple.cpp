#include "Apple.h"

Apple::Apple(sf::Image assets[]) {
    hitbox.setSize(sf::Vector2f(25, 25));
    sprite.loadFromImage(assets[14]);
    hitbox.setTexture(&sprite);
}

void Apple::Apple_gen(Snake* snake)
{
    srand(time(NULL));
    do
    {
        x = rand() % 31;
        y = rand() % 23;
    } while (snake->in_snake(x, y));
}

void Apple::draw_Apple(sf::RenderWindow* window_ptr)
{
    hitbox.setPosition(x * 25, y * 25);
    window_ptr->draw(hitbox);
}
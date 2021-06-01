#include "Segment.h"

Segment::Segment(int dir, int tx, int ty, sf::Image assets[], int texture_id )
{
    spr_id = texture_id;
    direction = dir;
    x = tx;
    y = ty;
    hitbox.setSize(sf::Vector2f(25, 25));
    sprite.loadFromImage(assets[texture_id]);
    hitbox.setTexture(&sprite);
}
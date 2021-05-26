#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Segment
{
public:
    int x, y, direction;
    sf::RectangleShape hitbox;
    sf::Texture sprite;
    Segment* next;
    Segment(int dir, int tx, int ty, string sprite_path) {
        direction = dir;
        x = tx;
        y = ty;
        hitbox.setSize(sf::Vector2f(25, 25));
        sprite.loadFromFile(sprite_path);
        hitbox.setTexture(&sprite);
    }
};

class Snake
{
public:
    int direction, score;
    Segment* head;
    void change_dir(int x)
    {
        direction = x;
    }
    void move()
    {
        switch (direction)
        {
        case 1:
            head->y--;
            break;

        case 2:
            if (head->x < 31)
                head->x++;
            else
                head->x = 0;
            break;

        case 3:
            head->y++;
            break;

        case 4:
            head->x--;
            break;
        }
    }
    void draw_snake(sf::RenderWindow* window_ptr)
    {
        Segment* _tmp = head;
        while (_tmp != NULL) {
            _tmp->hitbox.setPosition(_tmp->x * 25, _tmp->y * 25);
            window_ptr->draw(_tmp->hitbox);
            _tmp = _tmp->next;
        }
    }
};

void swapper(int* x, int* y)
{
    int _tmp;
    _tmp = *x;
    *x = *y;
    *y = _tmp;
}

Snake* init_snake()
{
    Segment* head = new Segment(2, 0, 0, "./Textures/snake_head.png");
    Snake* init_snake = new Snake;
    init_snake->head = head;
    init_snake->direction = 2;
    return init_snake;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    Snake* main_snake = init_snake();
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        cout << "Coords: " << main_snake->head->x << ", " << main_snake->head->y << " ; direction: " << main_snake->direction << endl;
        window.clear();
        main_snake->draw_snake(&window);
        window.display();
        main_snake->move();
        sf::sleep(sf::milliseconds(500));
    }

    return 0;
}
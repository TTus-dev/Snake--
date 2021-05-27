#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

sf::Image Asset_container[15];

class Game_object
{
public:
    int x, y;
    sf::Texture sprite;
    sf::RectangleShape hitbox;
};

class Apple : public Game_object
{
public:
    Apple()
    {
        srand(time(NULL));

        x = rand() % 31;
        y = rand() % 23;

        hitbox.setSize(sf::Vector2f(25, 25));
        sprite.loadFromImage(Asset_container[14]);
        hitbox.setTexture(&sprite);
    }
    void Apple_gen()
    {
        srand(time(NULL));

        x = rand() % 31;
        y = rand() % 23;
    }
    void draw_Apple(sf::RenderWindow* window_ptr)
    {
        hitbox.setPosition(x * 25, y * 25);
        window_ptr->draw(hitbox);
    }
};

class Segment : public Game_object
{
public:
    int direction;
    Segment *next;
    Segment(int dir, int tx, int ty, int texture_id)
    {
        direction = dir;
        x = tx;
        y = ty;
        hitbox.setSize(sf::Vector2f(25, 25));
        sprite.loadFromImage(Asset_container[texture_id]);
        hitbox.setTexture(&sprite);
    }
};

void swapper(int* x, int* y)
{
    int _tmp;
    _tmp = *x;
    *x = *y;
    *y = _tmp;
}

class Snake
{
public:
    int direction, score;
    Segment* head;
    void set_dir(int x)
    { 
        direction = x;
        head->direction = x;
    }

    void update_sprites()
    {
        head->sprite.loadFromImage(Asset_container[head->direction - 1]);
        head->hitbox.setTexture(&head->sprite);
        Segment* _iter = head->next;
        int prev_dir = head->direction;
        while (_iter->next != NULL) {
            if (prev_dir != _iter->direction) {
                if (prev_dir == 1) {
                    if (_iter->direction == 2) { _iter->sprite.loadFromImage(Asset_container[5]); }
                    else { _iter->sprite.loadFromImage(Asset_container[4]); }
                }

                else if (prev_dir == 2) {
                    if (_iter->direction == 3) { _iter->sprite.loadFromImage(Asset_container[4]); }
                    else { _iter->sprite.loadFromImage(Asset_container[6]); }
                }

                else if (prev_dir == 3) {
                    if (_iter->direction == 2) { _iter->sprite.loadFromImage(Asset_container[7]); }
                    else { _iter->sprite.loadFromImage(Asset_container[6]); }
                }

                else if (prev_dir == 4) {
                    if (_iter->direction == 3) { _iter->sprite.loadFromImage(Asset_container[5]); }
                    else { _iter->sprite.loadFromImage(Asset_container[7]); }
                }
            }
            else
            {
                if (_iter->direction == 1 || _iter->direction == 3) { _iter->sprite.loadFromImage(Asset_container[13]); }
                else { _iter->sprite.loadFromImage(Asset_container[12]); }
            }
            _iter->hitbox.setTexture(&_iter->sprite);
            prev_dir = _iter->direction;
            _iter = _iter->next;
        }
        _iter->sprite.loadFromImage(Asset_container[prev_dir + 7]);
        _iter->hitbox.setTexture(&_iter->sprite);
    }

    void move()
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
        while (_iter != NULL) {
            swapper(&_iter->x, &old_x);
            swapper(&_iter->y, &old_y);
            swapper(&_iter->direction, &old_dir);
            _iter = _iter->next;
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

Snake* init_snake()
{
    Segment* head = new Segment(2, 2, 0, 1);
    head->next = new Segment(2, 1, 0, 12);
    head->next->next = new Segment(2, 0, 0, 9);
    Snake* init_snake = new Snake;
    init_snake->head = head;
    init_snake->set_dir(2);
    return init_snake;
}

void Load_sprites()
{
    for (int i = 0; i < 15; i++)
    {
        Asset_container[i].loadFromFile("./Textures/" + to_string(i + 1) + ".png");
    }
}


int main()
{
    Load_sprites();
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    Apple* main_apple = new Apple;
    Snake* main_snake = init_snake();

    sf::Clock clock;
    float timer = 0, delay = 0.1;

    int next_dir = 2, old_dir = 2;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        if (timer > delay) {
            timer = 0;
            main_snake->update_sprites();
            main_snake->move();
            old_dir = main_snake->direction;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (old_dir != 2) { main_snake->set_dir(4); }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (old_dir != 3){ main_snake->set_dir(1); }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (old_dir != 4) { main_snake->set_dir(2); }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (old_dir != 1) { main_snake->set_dir(3); }
        }

        window.clear();
        main_apple->draw_Apple(&window);
        main_snake->draw_snake(&window);
        window.display();
    }

    return 0;
}
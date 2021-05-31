#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include "Snake.h"
#include "Apple.h"
#include "Segment.h"
#include "Menu.h"

using namespace std;

sf::Image Asset_container[15];

Snake* init_snake()
{
    Segment* head = new Segment(2, 2, 0, Asset_container, 1);
    head->next = new Segment(2, 1, 0, Asset_container, 12);
    head->next->next = new Segment(2, 0, 0, Asset_container, 9);
    Snake* init_snake = new Snake;
    init_snake->head = head;
    init_snake->set_dir(2);
    return init_snake;
}

void Load_sprites()
{
    for (int i = 0; i < 15; i++)
    {
        Asset_container[i].loadFromFile("./Assets/Textures/" + to_string(i + 1) + ".png");
    }
}


int main()
{
    int Gamestate = 0;

    sf::Font main_font;

    Load_sprites();
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake", sf::Style::Close | sf::Style::Titlebar);
    window.setKeyRepeatEnabled(false);

    Apple main_apple(Asset_container);
    Snake* main_snake = init_snake();
    Menu main_menu(window.getSize().x, window.getSize().y);

    sf::Clock clock;
    float timer = 0, delay = 0.2;

    int next_dir = 2, old_dir = 2;

    bool isPaused = false;
    bool escState = false;
    bool growing = false;
    bool eaten = false;

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Gamestate == 0) {
            main_menu.draw(&window);
        }
        else if (Gamestate == 1) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                if (old_dir != 2) { main_snake->set_dir(4); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if (old_dir != 3) { main_snake->set_dir(1); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                if (old_dir != 4) { main_snake->set_dir(2); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (old_dir != 1) { main_snake->set_dir(3); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !escState)
            {
                if (isPaused) { isPaused = false; }
                else { isPaused = true; }
                escState = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { escState = false; }

            if (!eaten) { eaten = main_snake->eat(main_apple); };

            if (eaten) { main_apple.Apple_gen(); }

            if (timer > delay && !isPaused) {
                timer = 0;
                if (eaten)
                {
                    eaten = false;
                    main_snake->grow(Asset_container);
                    main_snake->update_sprites(true, Asset_container);
                    main_snake->move(true);
                }
                else
                {
                    main_snake->update_sprites(false, Asset_container);
                    main_snake->move(false);
                }
                old_dir = main_snake->direction;
            }
            main_apple.draw_Apple(&window);
            main_snake->draw_snake(&window);
        }
        window.display();
    }

    return 0;
}
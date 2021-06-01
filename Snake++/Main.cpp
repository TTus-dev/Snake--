#include <SFML/Graphics.hpp>
#include <iostream>
#include "Snake.h"
#include "Apple.h"
#include "Segment.h"
#include "Menu.h"
#include "DialogBox.h"

using namespace std;

sf::Image Asset_container[15];

Snake* init_snake()
{
    Segment* head = new Segment(2, 4, 5, Asset_container, 1);
    head->next = new Segment(2, 3, 5, Asset_container, 12);
    head->next->next = new Segment(2, 2, 5, Asset_container, 9);
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
    Menu main_menu(&window);
    DialogBox Pause(&window, 1);
    DialogBox GameOver(&window, 2);
    sf::Mouse main_mouse;

    sf::Clock clock;
    float timer = 0, delay = 0.2;

    int next_dir = 2, old_dir = 2;

    bool new_game = true;
    bool isPaused = false;
    bool keyboard = false;
    bool mouse = false;
    bool growing = false;
    bool eaten = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        if (Gamestate == 0) {
            main_menu.mouse_hover(main_mouse, &window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse)
            {
                switch (main_menu.selected_option)
                {
                case 0:
                    new_game = true;
                    isPaused = false;
                    Gamestate = 1;
                    break;

                case 2:
                    window.close();
                    break;

                default:
                    break;
                }
                continue;
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { mouse = false; }
            main_menu.draw(&window);
        }

        else if (Gamestate == 1) {

            if (new_game)
            {
                main_snake = init_snake();
                main_apple.Apple_gen(main_snake);
                new_game = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !keyboard)
            {
                if (old_dir != 2 && old_dir != 4) { main_snake->set_dir(4); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !keyboard)
            {
                if (old_dir != 3 && old_dir != 1) { main_snake->set_dir(1); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !keyboard)
            {
                if (old_dir != 4 && old_dir != 2) { main_snake->set_dir(2); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !keyboard)
            {
                if (old_dir != 1 && old_dir != 3) { main_snake->set_dir(3); }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !keyboard)
            {
                if (isPaused) { isPaused = false; }
                else { isPaused = true; }
                keyboard = true;
            }
            else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { keyboard = false; }

            if (!eaten) { eaten = main_snake->eat(main_apple.x, main_apple.y); }

            else{ main_apple.Apple_gen(main_snake);}

            if (timer > delay && !isPaused)
            {
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
            if (isPaused) {
                Pause.mouse_hover(main_mouse, &window);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse)
                {
                    switch (Pause.selected_option)
                    {
                    case 0:
                        isPaused = false;
                        break;

                    case 1:
                        Gamestate = 0;
                        break;

                    default:
                        break;
                    }
                    continue;
                }
                else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { mouse = false; }
                Pause.render(&window); 
            }
        }

        window.display();
        window.clear();
    }

    return 0;
}
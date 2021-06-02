#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Snake.h"
#include "Apple.h"
#include "Segment.h"
#include "Menu.h"
#include "DialogBox.h"

using namespace std;

sf::Image Asset_container[15];
sf::Image Background;

void Load_sprites()
{
    for (int i = 0; i < 15; i++)
    {
        Asset_container[i].loadFromFile("./Assets/Textures/" + to_string(i + 1) + ".png");
    }
}

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


int main()
{
    Load_sprites();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake", sf::Style::Close | sf::Style::Titlebar);
    window.setKeyRepeatEnabled(false);

    sf::Mouse main_mouse;

    sf::Clock clock;

    sf::Texture background_sprite;

    sf::RectangleShape bg_gameplay, green_bg;

    Apple main_apple(Asset_container);
    Snake* main_snake = init_snake();
    Menu main_menu(&window);
    DialogBox Pause(&window, 1), GameOver(&window, 2);

    background_sprite.loadFromFile("./Assets/Textures/background.png");
    bg_gameplay.setTexture(&background_sprite);
    bg_gameplay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    green_bg.setFillColor(sf::Color(170, 215, 81));
    green_bg.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    float timer, delay = 0.15f;
    int next_dir, old_dir, Gamestate = 0, Score = 0, Highscore = 0;
    bool new_game = true, isPaused = false, keyboard = false, mouse = false, growing = false, eaten = false;

    fstream highscore_file;
    highscore_file.open("highscore.txt", fstream::in);
    highscore_file >> Highscore;
    highscore_file.close();

    while (window.isOpen())
    {
        window.draw(green_bg);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (Gamestate == 0) 
        {
            main_menu.mouse_hover(main_mouse, &window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse)
            {
                switch (main_menu.selected_option)
                {
                case 1:
                    new_game = true;
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

        else if (Gamestate == 1)
        {
            window.draw(bg_gameplay);
            if (new_game)
            {
                main_snake = init_snake();
                old_dir = 2;
                next_dir = 2;
                timer = 0;
                main_apple.Apple_gen(main_snake);
                new_game = false;
                Score = 0;
                isPaused = false;
            }

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

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

            else
            {
                Score++;
                if (Score < 765) {
                    main_apple.Apple_gen(main_snake);
                    eaten = false;
                    growing = true;
                }
                else { Gamestate = 2; continue; }
            }

            if (timer > delay && !isPaused)
            {
                timer = 0;
                if (growing)
                {
                    growing = false;
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

            if (main_snake->in_snake(0))
            {
                Gamestate = 2;
                continue;
            }

            main_apple.draw_Apple(&window);
            main_snake->draw_snake(&window);
            if (isPaused) {
                Pause.mouse_hover(main_mouse, &window);
                Pause.set_subtitle(&window, Score);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse)
                {
                    mouse = true;
                    switch (Pause.selected_option)
                    {
                    case 2:
                        isPaused = false;
                        break;

                    case 3:
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

        else if (Gamestate == 2)
        {
            GameOver.mouse_hover(main_mouse, &window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouse)
            {
                mouse = true;
                switch (GameOver.selected_option)
                {
                case 2:
                    new_game = true;
                    Gamestate = 1;
                    break;

                case 3:
                    Gamestate = 0;
                    break;

                default:
                    break;
                }
            }
            else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { mouse = false; }
            if (Score == 765)
            {
                main_snake->draw_snake(&window);
            }
            GameOver.set_subtitle(&window, Score, Highscore);
            GameOver.render(&window);
        }
        window.display();
        window.clear();
    }

    if (Score > Highscore)
        Highscore = Score;
    highscore_file.open("highscore.txt", fstream::out | fstream::trunc);
    highscore_file << Highscore;
    highscore_file.close();

    return 0;
}
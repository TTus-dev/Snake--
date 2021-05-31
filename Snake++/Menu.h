#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	int selected_option;
	sf::Font main_font;
	sf::Text test;
	sf::Text options_array[3];
	Menu(int window_x, int window_y);
	void draw(sf::RenderWindow *window);
	void option_up();
	void option_down();
};
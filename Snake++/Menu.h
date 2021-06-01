#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
	sf::Font main_font;
	sf::Text options_array[3];
public:
	int selected_option;
	Menu(sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void change_selected(int n);
	void mouse_hover(sf::Mouse mouse, sf::RenderWindow* window);
	void clear_selected();
};
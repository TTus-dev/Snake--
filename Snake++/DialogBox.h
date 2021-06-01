#pragma once
#include <SFML/Graphics.hpp>

class DialogBox
{
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font main_font;
	sf::Text dialog_options_array[2];
public:
	int selected_option;
	DialogBox(sf::RenderWindow *window, int type);
	void mouse_hover(sf::Mouse mouse, sf::RenderWindow* window);
	void render(sf::RenderWindow *window);
	void change_selected(int n);
	void clear_selected();
};
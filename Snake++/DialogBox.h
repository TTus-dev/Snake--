#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class DialogBox
{
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Font main_font;
	sf::Text dialog_options_array[4];
public:
	int selected_option;
	DialogBox(sf::RenderWindow *window, int type);
	void mouse_hover(sf::Mouse mouse, sf::RenderWindow* window);
	void render(sf::RenderWindow *window);
	void change_selected(int n);
	void clear_selected();
	void set_subtitle( sf::RenderWindow* window, int score, int highscore = -1 );
};
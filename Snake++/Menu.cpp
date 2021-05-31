#include "Menu.h"
#include <iostream>

Menu::Menu(int window_x, int window_y) {
	
	sf::FloatRect bnds;
	main_font.loadFromFile("./Assets/Fonts/arial.ttf");

	options_array[0].setFillColor(sf::Color::Green);
	options_array[0].setString("Graj");
	options_array[1].setFillColor(sf::Color::White);
	options_array[1].setString("Wyniki");
	options_array[2].setFillColor(sf::Color::White);
	options_array[2].setString(L"Wyjdü");

	for (int i = 0; i < 3; i++)
	{
		options_array[i].setFont(main_font);
		bnds = options_array[i].getLocalBounds();
		std::cout << bnds.width << " " << bnds.height << " " << bnds.left << " " << bnds.top << "\n";
		options_array[i].setOrigin(bnds.left + bnds.width / 2.0f, bnds.top + bnds.height / 2.0f);
		options_array[i].setPosition(window_x / 2, window_y / 5 * (i + 2));
	}
}

void Menu::draw(sf::RenderWindow *window)
{
	if (window != nullptr) {
		for (int i = 0; i < 3; i++) {
			window->draw(options_array[i]);
		}
	}
}
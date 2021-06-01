#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* window) {

	selected_option = -1;
	
	sf::FloatRect bnds;
	main_font.loadFromFile("./Assets/Fonts/arial.ttf");

	options_array[0].setString("Graj");
	options_array[1].setString("Wyniki");
	options_array[2].setString(L"Wyjdü");

	for (int i = 0; i < 3; i++)
	{
		options_array[i].setFillColor(sf::Color::White);
		options_array[i].setFont(main_font);
		bnds = options_array[i].getLocalBounds();
		options_array[i].setOrigin(bnds.width / 2.0f, bnds.height / 2.0f);
		options_array[i].setPosition(window->getSize().x / 2, window->getSize().y / 5 * (i + 2));
	}
}

void Menu::draw(sf::RenderWindow* window)
{
	if (window != nullptr)
	{
		for (int i = 0; i < 3; i++)
		{
			window->draw(options_array[i]);
		}
	}
}

void Menu::mouse_hover(sf::Mouse mouse, sf::RenderWindow* window)
{
	for (int i = 0; i < 3; i++)
	{
		if (options_array[i].getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
		{
			change_selected(i);
			break;
		}
		clear_selected();
	}
}

void Menu::change_selected(int n)
{
	if (selected_option != - 1)
		options_array[selected_option].setFillColor(sf::Color::White);
	options_array[n].setFillColor(sf::Color::Green);
	selected_option = n;
}

void Menu::clear_selected()
{
	for (int i = 0; i < 3; i++)
	{
		options_array[i].setFillColor(sf::Color::White);
	}
	selected_option = -1;
}
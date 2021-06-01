#include "DialogBox.h"

DialogBox::DialogBox(sf::RenderWindow *window, int type)
{
	main_font.loadFromFile("./Assets/Fonts/arial.ttf");
	if (type == 1) { dialog_options_array[0].setString("Wznów"); }
	else { dialog_options_array[0].setString("Restart"); }

	dialog_options_array[1].setString(L"Menu g³ówne");

	for (int i = 0 ; i < 2; i++)
	{
		dialog_options_array[i].setFillColor(sf::Color::White);
		dialog_options_array[i].setFont(main_font);
		sf::FloatRect bnds = dialog_options_array[i].getLocalBounds();
		dialog_options_array[i].setOrigin(bnds.width / 2.0f, bnds.height / 2.0f);
		dialog_options_array[i].setPosition(window->getSize().x / 2, window->getSize().y / 4 * (i + 1.5f));
	}

	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setFillColor(sf::Color(20, 20, 20, 100));

	container.setSize(sf::Vector2f(window->getSize().x / 3.f, window->getSize().y));
	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(window->getSize().x / 2 - container.getSize().x / 2 , 0.f);
}

void DialogBox::render(sf::RenderWindow* window)
{
	if (window != nullptr)
	{
		window->draw(background);
		window->draw(container);
		for (auto i : dialog_options_array)
		{
			window->draw(i);
		}
	}
}

void DialogBox::mouse_hover(sf::Mouse mouse, sf::RenderWindow* window)
{
	for (int i = 0; i < 2; i++)
	{
		if (dialog_options_array[i].getGlobalBounds().contains(mouse.getPosition(*window).x, mouse.getPosition(*window).y))
		{
			change_selected(i);
			break;
		}
		clear_selected();
	}
}

void DialogBox::change_selected(int n)
{
	if (selected_option != -1)
		dialog_options_array[selected_option].setFillColor(sf::Color::White);
	dialog_options_array[n].setFillColor(sf::Color::Green);
	selected_option = n;
}

void DialogBox::clear_selected()
{
	for (int i = 0; i < 3; i++)
	{
		dialog_options_array[i].setFillColor(sf::Color::White);
	}
	selected_option = -1;
}
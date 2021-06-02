#include "DialogBox.h"

DialogBox::DialogBox(sf::RenderWindow *window, int type)
{
	main_font.loadFromFile("./Assets/Fonts/arial.ttf");
	if (type == 1)
	{
		dialog_options_array[2].setString("Wznów");
		dialog_options_array[0].setString("Pauza");
	}
	else
	{
		dialog_options_array[2].setString("Restart");
		dialog_options_array[0].setString("Koniec gry!");
	}
	dialog_options_array[3].setString(L"Menu g³ówne");
	dialog_options_array[0].setCharacterSize(72);

	for (int i = 0 ; i < 4; i++)
	{
		dialog_options_array[i].setFillColor(sf::Color::White);
		dialog_options_array[i].setFont(main_font);
		sf::FloatRect bnds = dialog_options_array[i].getLocalBounds();
		dialog_options_array[i].setOrigin(bnds.width / 2.0f, bnds.height / 2.0f);
		dialog_options_array[i].setPosition(window->getSize().x / 2, window->getSize().y / 4.7 * (i + 0.7f));
	}

	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setFillColor(sf::Color(20, 20, 20, 100));

	float title_width = dialog_options_array[0].getGlobalBounds().width;
	container.setSize(sf::Vector2f(title_width + 100 , window->getSize().y));
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
	for (int i = 2; i < 4; i++)
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
	for (int i = 2; i < 4; i++)
	{
		dialog_options_array[i].setFillColor(sf::Color::White);
	}
	selected_option = -1;
}

void DialogBox::set_subtitle(sf::RenderWindow* window, int score, int highscore)
{
	if (score > highscore && highscore > 0)
		dialog_options_array[1].setString("Nowy rekord: " + std::to_string(score));
	else
		dialog_options_array[1].setString("Twój wynik: " + std::to_string(score));
	sf::FloatRect bnds = dialog_options_array[1].getLocalBounds();
	dialog_options_array[1].setOrigin(bnds.width / 2.0f, bnds.height / 2.0f);
	dialog_options_array[1].setPosition(window->getSize().x / 2, window->getSize().y / 4.7 * (1 + 0.7f));
}
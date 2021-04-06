#include "Header.h"

void DisplayStartScreen(sf::RenderWindow * window)
{
	sf::Texture texture;
	texture.loadFromFile("../Textures/StartScreen.png");

	sf::RectangleShape background(sf::Vector2f(1280.0f, 960.0f));
	background.setTexture(&texture);

	window->draw(background);
	window->display();
}

void WriteCharacterDescription(char charClass, sf::RenderWindow * window)
{
	sf::Font font;
	font.loadFromFile("ink-free-normal.ttf");
	sf::Text text("", font);
	sf::Text stats("", font);
	text.setCharacterSize(35);
	stats.setCharacterSize(45);
	text.setFillColor(sf::Color::White);
	stats.setFillColor(sf::Color::White);
	text.move(sf::Vector2f(810, 150));
	stats.move(sf::Vector2f(810, 550));
	switch (charClass)
	{
	case 'k':
		text.setString("Knight\nA noble warrior equipped\nwith a sword and thickshield.\nCan withstand many attacks.");
		stats.setString("Strength: 10\nDefence: 15\nEndurance: 15\nIntelligence: 12");
		break;
	case 'p':
		text.setString("Priestess\nSkilled with magic of light,\nthe priestess uses her divine\naura to protect herself\nas well as lay waste\nto her enemies");
		stats.setString("Strength: 10\nDefence: 12\nEndurance: 12\nIntelligence: 15");
		break;
	case 'b':
		text.setString("Barbarian\nA fearsome fighter who sows\ndestruction with his\nmighty axe.");
		stats.setString("Strength: 15\nDefence: 10\nEndurance: 12\nIntelligence: 8");
		break;
	case 'w':
		text.setString("Witch\nA powerful sorceress.\nHer knowledge of arcane spells\nmakes her unstoppable.");
		stats.setString("Strength: 15\nDefence: 8\nEndurance: 10\nIntelligence: 18");
		break;
	}
	window->draw(text);
	window->draw(stats);
}

int DisplayClassCharacteristics(sf::RenderWindow * window, sf::RectangleShape * Portraits)
{
	int PortraitHeight = Portraits[0].getSize().y;
	int PortraitWidth = Portraits[0].getSize().x;
	float windowOffsetX = window->getPosition().x;
	float windowOffsetY = window->getPosition().y;
	if (sf::Mouse::getPosition().x > Portraits[0].getPosition().x + windowOffsetX && sf::Mouse::getPosition().x < Portraits[0].getPosition().x + PortraitWidth + windowOffsetX)
	{
		if (sf::Mouse::getPosition().y > Portraits[0].getPosition().y + windowOffsetY && sf::Mouse::getPosition().y < Portraits[0].getPosition().y + windowOffsetY + PortraitHeight)
		{
			WriteCharacterDescription('k', window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				return 1;
			}
		}
		else if (sf::Mouse::getPosition().y > Portraits[1].getPosition().y + windowOffsetY && sf::Mouse::getPosition().y < Portraits[1].getPosition().y + windowOffsetY + PortraitHeight)
		{
			WriteCharacterDescription('p', window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				return 2;
			}
		}
	}
	if (sf::Mouse::getPosition().x > Portraits[2].getPosition().x + windowOffsetX && sf::Mouse::getPosition().x < Portraits[2].getPosition().x + PortraitWidth + windowOffsetX)
	{
		if (sf::Mouse::getPosition().y > Portraits[2].getPosition().y + windowOffsetY && sf::Mouse::getPosition().y < Portraits[2].getPosition().y + windowOffsetY + PortraitHeight)
		{
			WriteCharacterDescription('b', window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				return 3;
			}
		}
		else if (sf::Mouse::getPosition().y > Portraits[3].getPosition().y + windowOffsetY && sf::Mouse::getPosition().y < Portraits[3].getPosition().y + windowOffsetY + PortraitHeight)
		{
			WriteCharacterDescription('w', window);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				return 4;
			}
		}
	}
	return false;
}

int DisplayClassSelection(sf::RenderWindow * window)
{
	sf::RectangleShape knightport;
	knightport.setSize(sf::Vector2f(172, 194));
	knightport.setPosition(sf::Vector2f(92, 210));

	sf::RectangleShape barbarianport;
	barbarianport.setSize(sf::Vector2f(172, 194));
	barbarianport.setPosition(sf::Vector2f( 432, 210));

	sf::RectangleShape priestessport;
	priestessport.setSize(sf::Vector2f(172, 194));
	priestessport.setPosition(sf::Vector2f( 92,  500));

	sf::RectangleShape witchport;
	witchport.setSize(sf::Vector2f(172, 194));
	witchport.setPosition(sf::Vector2f(432, 500));

	sf::RectangleShape PortraitsTab[] = { knightport, priestessport, barbarianport, witchport };

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("../Textures/ClassSelection.png");
	sf::RectangleShape background(sf::Vector2f(1280.0f, 960.0f));
	background.setTexture(&backgroundTexture);

	sf::Texture knightText;
	knightText.loadFromFile("../Textures/knightport.png");
	knightport.setTexture(&knightText);

	sf::Texture barbarianText;
	barbarianText.loadFromFile("../Textures/barbarianport.png");
	barbarianport.setTexture(&barbarianText);

	sf::Texture priestessText;
	priestessText.loadFromFile("../Textures/priestessport.png");
	priestessport.setTexture(&priestessText);

	sf::Texture witchText;
	witchText.loadFromFile("../Textures/witchport.png");
	witchport.setTexture(&witchText);

	int CharacterChoice;
	while (true)
	{
		window->draw(background);
		window->draw(knightport);
		window->draw(barbarianport);
		window->draw(priestessport);
		window->draw(witchport);
		CharacterChoice = DisplayClassCharacteristics(window, PortraitsTab);
		if (CharacterChoice > 0)
		{
			return CharacterChoice; 
		}

		window->display();
		window->clear();
	}
}
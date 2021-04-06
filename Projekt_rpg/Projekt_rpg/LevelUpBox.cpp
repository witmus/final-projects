#include "LevelUpBox.h"

LevelUpBox::LevelUpBox(sf::RenderWindow * window_, Character * character) :window(window_), hero(character), box(sf::Vector2f(480, 360)), stats("", font)
{
	SkillPoints = 3;
	font.loadFromFile("ink-free-normal.ttf");
	stats.setCharacterSize(40);
	stats.setLineSpacing(1.4);
	stats.setPosition(sf::Vector2f(520, 320));
	texture.loadFromFile("../Textures/lvlupbox.png");
	button.loadFromFile("../Textures/button.png");
	box.setPosition(sf::Vector2f(400, 300));
	box.setTexture(&texture);
	for (int i = 0; i < 4; i++)
	{
		buttons.push_back(sf::RectangleShape(sf::Vector2f(35, 35)));
		buttons[i].setPosition(sf::Vector2f(200 + box.getPosition().x, 25 + 70 * i + box.getPosition().y));
		buttons[i].setTexture(&button);
	}
}

LevelUpBox::~LevelUpBox()
{
}

void LevelUpBox::GetInput()
{
	sf::Vector2i mp = sf::Mouse::getPosition();
	sf::Vector2i wp = window->getPosition();
	int buttonX = buttons[0].getPosition().x;
	int input = 0;
	
	if (mp.x > buttonX + wp.x && mp.x < buttonX + buttons[0].getSize().x + wp.x)
	{
		for (int i = 0; i < 4; i++)
		{
			if (mp.y >= buttons[i].getPosition().y + wp.y + buttons[i].getSize().y && mp.y <= buttons[i].getPosition().y + buttons[i].getSize().y + buttons[i].getSize().y + wp.y)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					input = i + 1;
					SkillPoints--;
					while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						sf::sleep(sf::microseconds(5));
					}
				}
			}
		}
		switch (input)
		{
		case 1:
			hero->IncrementAttack();
			break;
		case 2:
			hero->IncrementDefence();
			break;
		case 3:
			hero->IncrementEndurance();
			break;
		case 4:
			hero->IncrementIntelligence();
			break;
		default:
			break;
		}
	}
}

void LevelUpBox::DisplayStats()
{
	stats.setString(std::to_string(hero->GetAttack()) + '\n' + std::to_string(hero->GetDefence()) + '\n' + std::to_string(hero->GetEndurance()) + '\n' + std::to_string(hero->GetIntelligence()));
	window->draw(stats);
}

void LevelUpBox::DisplayBox()
{
	window->draw(box);
	for (int i = 0; i < 4; i++)
	{
		window->draw(buttons[i]);
	}
}

void LevelUpBox::RunBox()
{
	while (SkillPoints > 0)
	{
		window->clear(sf::Color::Color());
		DisplayBox();
		DisplayStats();
		window->display();
		GetInput();
	}
	hero->SetHealthLimit();
	hero->SetHealth(hero->GetHealthLimit());
	hero->SetManaLimit();
	hero->SetMana(hero->GetManaLimit());
}
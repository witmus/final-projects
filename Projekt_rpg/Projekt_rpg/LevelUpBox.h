#pragma once
#include "Character.h"

class LevelUpBox
{
	sf::RenderWindow * window;
	sf::Texture texture;
	sf::Texture button;
	sf::RectangleShape box;
	std::vector<sf::RectangleShape> buttons;
	sf::Font font;
	sf::Text stats;
	Character * hero;

	int SkillPoints;

public:
	LevelUpBox(sf::RenderWindow * window_, Character * character);
	~LevelUpBox();

	void DisplayBox();
	void DisplayStats();
	void GetInput();
	void RunBox();
};


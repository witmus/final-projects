#pragma once
#include "Character.h"
class Barbarian :public Character
{
	sf::Texture text;
	sf::RectangleShape sprite;
public:
	Barbarian(sf::RenderWindow * window);
	~Barbarian();

	virtual void DisplaySprite(sf::RenderWindow * window);
	virtual void InitializeSkillset();
};


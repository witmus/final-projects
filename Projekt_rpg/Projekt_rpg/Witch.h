#pragma once
#include "Character.h"
class Witch :public Character
{
	sf::Texture text;
	sf::RectangleShape sprite;
public:
	Witch(sf::RenderWindow * window);
	~Witch();

	virtual void DisplaySprite(sf::RenderWindow * window);
	virtual void InitializeSkillset();
};


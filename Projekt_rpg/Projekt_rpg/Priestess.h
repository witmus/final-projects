#pragma once
#include "Character.h"
class Priestess : public Character
{
	sf::Texture text;
	sf::RectangleShape sprite;
public:
	Priestess(sf::RenderWindow * window);
	~Priestess();

	virtual void DisplaySprite(sf::RenderWindow * window);
	virtual void InitializeSkillset();
};


#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"

class Knight :public Character
{
	sf::Texture text;
	sf::RectangleShape sprite;
public:
	Knight(sf::RenderWindow * window);
	~Knight();

	virtual void DisplaySprite(sf::RenderWindow * window);
	virtual void InitializeSkillset();
};

#endif
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy :public Character
{
	sf::Texture text;
	sf::RectangleShape sprite;

public:
	
	Enemy(int level);
	~Enemy();

	bool Attack();

	virtual void DisplaySprite(sf::RenderWindow * window);
	virtual void InitializeSkillset();
};

#endif
#include "Enemy.h"

Enemy::Enemy(int level) :sprite(sf::Vector2f(70, 100))
{
	attack = 5 + level * 3;
	defence = 5 + level * 3;
	endurance = 8 + level * 3;
	intelligence = 0;

	hp_limit = endurance * 10;
	hp = hp_limit;

	mana_limit = intelligence * 10;
	mana = mana_limit;

	red_potions = 0;
	blue_potions = 0;

	currentState = CLEAN;
	state_duration = 0;

	text.loadFromFile("../Textures/skeleton_big.png");
	sprite.setTexture(&text);
	sprite.setPosition(sf::Vector2f(750, 165));
}

Enemy::~Enemy()
{
}

bool Enemy::Attack()
{
	if (currentState != STUN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::DisplaySprite(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Enemy::InitializeSkillset()
{
}

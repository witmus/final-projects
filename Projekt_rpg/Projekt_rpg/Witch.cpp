#include "Witch.h"

Witch::Witch(sf::RenderWindow * w) :sprite(sf::Vector2f(50, 65))
{
	window = w;
	attack = 15;
	defence = 8;
	endurance = 10;
	intelligence = 18;

	hp_limit = endurance * 10;
	hp = hp_limit;

	mana_limit = intelligence * 10;
	mana = mana_limit;

	red_potions = 2;
	blue_potions = 2;

	level = 1;
	experience = 0;
	currentState = CLEAN;
	state_duration = 0;

	text.loadFromFile("../Textures/map_sprites_final.png");
	sprite.setTexture(&text);
	sf::Vector2u textureSize = text.getSize();
	textureSize.x /= 4;
	textureSize.y /= 4;
	sprite.setTextureRect(sf::IntRect(textureSize.x, textureSize.y * 3, textureSize.x, textureSize.y));
	sprite.setPosition(sf::Vector2f(450, 200));

	skillset = nullptr;
}

Witch::~Witch()
{
	
}

void Witch::DisplaySprite(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Witch::InitializeSkillset()
{
	Effect fireball[2] = { DEAL_DAMAGE, CLEAN };
	Effect freeze[2] = { STUN, CLEAN };
	Effect drain[2] = { DEAL_DAMAGE, HEAL };
	Skill * tab = new Skill[3];
	tab[0] = Skill::Skill(3, fireball, window);
	tab[1] = Skill::Skill(2, freeze, window);
	tab[2] = Skill::Skill(1, drain, window);
	for (int i = 0; i < 3; i++)
	{
		tab[i].SetIcon(i, 3);
		tab[i].SetIconPosition(200 + 400 * i, 650);
	}
	skillset = tab;
}

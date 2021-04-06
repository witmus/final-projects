#include "Barbarian.h"

Barbarian::Barbarian(sf::RenderWindow * w) :sprite(sf::Vector2f(50, 65))
{
	window = w;
	attack = 16;
	defence = 10;
	endurance = 12;
	intelligence = 8;

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
	sprite.setTextureRect(sf::IntRect(textureSize.x, textureSize.y*2, textureSize.x, textureSize.y));
	sprite.setPosition(sf::Vector2f(450, 200));

	skillset = nullptr;
}

Barbarian::~Barbarian()
{
	
}

void Barbarian::DisplaySprite(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Barbarian::InitializeSkillset()
{
	Effect stun[2] = { STUN, DEAL_DAMAGE };
	Effect execute[2] = { DEAL_DAMAGE, CLEAN };
	Effect frenzy[2] = { RAISE_ATTACK, HEAL };
	Skill * tab = new Skill[3];
	tab[0] = Skill::Skill(2, stun, window);
	tab[1] = Skill::Skill(3, execute, window);
	tab[2] = Skill::Skill(2, frenzy, window);
	for (int i = 0; i < 3; i++)
	{
		tab[i].SetIcon(i, 2);
		tab[i].SetIconPosition(200 + 400 * i, 650);
	}
	skillset = tab;
}

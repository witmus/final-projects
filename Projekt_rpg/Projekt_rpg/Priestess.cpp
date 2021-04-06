#include "Priestess.h"

Priestess::Priestess(sf::RenderWindow * w) :sprite(sf::Vector2f(50, 65))
{
	window = w;
	attack = 10;
	defence = 12;
	endurance = 12;
	intelligence = 15;

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
	sprite.setTextureRect(sf::IntRect(textureSize.x, textureSize.y, textureSize.x, textureSize.y));
	sprite.setPosition(sf::Vector2f(450, 200));

	skillset = nullptr;
}

Priestess::~Priestess()
{
	
}

void Priestess::DisplaySprite(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Priestess::InitializeSkillset()
{
	Effect divineshield[2] = { GRANT_IMMUNITY, CLEAN };
	Effect bolt[2] = { STUN, DEAL_DAMAGE };
	Effect heal[2] = { HEAL, HEAL };
	Skill * tab = new Skill[3];
	tab[0] = Skill::Skill(3, divineshield, window);
	tab[1] = Skill::Skill(2, bolt, window);
	tab[2] = Skill::Skill(2, heal, window);
	for (int i = 0; i < 3; i++)
	{
		tab[i].SetIcon(i, 1);
		tab[i].SetIconPosition(200 + 400 * i, 650);
	}
	skillset = tab;
}

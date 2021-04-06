#include "Knight.h"

Knight::Knight(sf::RenderWindow * w) :sprite(sf::Vector2f(50, 65))
{
	window = w;
	attack = 10;
	defence = 15;
	endurance = 15;
	intelligence = 12;

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
	sprite.setTextureRect(sf::IntRect(textureSize.x, 0, textureSize.x, textureSize.y));
	sprite.setPosition(sf::Vector2f(450, 200));

	skillset = nullptr;
}

Knight::~Knight()
{
	
}

void Knight::DisplaySprite(sf::RenderWindow * window)
{
	window->draw(sprite);
}

void Knight::InitializeSkillset()
{
	Effect slam[2] = { DEAL_DAMAGE, STUN };
	Effect retaliation[2] = { RAISE_DEFENCE, DEAL_DAMAGE };
	Effect intervention[2] = { RAISE_ATTACK, HEAL };
	Skill * tab = new Skill[3];
	tab[0] = Skill::Skill(3, slam, window);
	tab[1] = Skill::Skill(2, retaliation, window);
	tab[2] = Skill::Skill(2, intervention, window);
	for (int i = 0; i < 3; i++)
	{	
		tab[i].SetIcon(i, 0);
		tab[i].SetIconPosition(200 + 400 * i, 650);
	}
	skillset = tab;

}

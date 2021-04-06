#include "Skill.h"

Skill::Skill()
{

}

Skill::Skill(int p,  Effect * e, sf::RenderWindow * w): power(p), icon(sf::Vector2f(80, 60)), window(w)
{
	texture.loadFromFile("../Textures/skillicons.png");
	effects = new Effect[2];
	effects[0] = e[0];
	effects[1] = e[1];
}

void Skill::SetIcon(int x, int y)
{
	sf::Vector2u textSize = texture.getSize();
	textSize.x /= 3;
	textSize.y /= 4;
	icon.setTexture(&texture);
	icon.setTextureRect(sf::IntRect(textSize.x * x, textSize.y * y, textSize.x, textSize.y));
}

void Skill::SetIconPosition(int x, int y)
{
	icon.setPosition(sf::Vector2f(x, y));
}

int Skill::GetPower()
{
	return power;
}

Effect * Skill::GetEffects()
{
	return effects;
}

sf::Vector2f Skill::GetIconPosition()
{
	return icon.getPosition();
}

void Skill::DisplayIcon()
{
	window->draw(icon);
}

Skill::~Skill()
{

}
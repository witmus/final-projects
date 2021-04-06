#ifndef SKILL_H
#define SKILL_H

#include "Header.h"

typedef enum Effect {DEAL_DAMAGE, STUN, RAISE_ATTACK, RAISE_DEFENCE, HEAL, GRANT_IMMUNITY, CLEAN};

class Skill
{
	sf::RenderWindow * window;
	sf::Texture texture;
	sf::RectangleShape icon;

	int power;

	Effect * effects;

public:
	Skill();
	Skill(int p, Effect * e, sf::RenderWindow * window);
	void SetIcon(int x, int y);
	void SetIconPosition(int x, int y);

	int GetPower();

	Effect * GetEffects();
	sf::Vector2f GetIconPosition();
	void DisplayIcon();
	~Skill();
};

#endif
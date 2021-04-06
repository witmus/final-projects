#ifndef CHARACTER_H
#define CHARACTER_H

#include "Header.h"
#include "Skill.h"

class Character
{
protected:
	sf::RenderWindow * window;

	int attack;
	int defence;
	int endurance;
	int intelligence;
	int mana;
	int mana_limit;
	int hp;
	int hp_limit;
	float experience;
	int level;
	int state_duration;

	int red_potions;
	int blue_potions;
	

	Skill * skillset;
	Effect currentState;
public:
	//auxiliary variable for skills altering stats
	//once the effect wears off temp is substracted
	//from the altered stat
	int temp;

	void Attack(Character * target);

	std::vector<int> getStats();
	int GetAttack();
	int GetDefence();
	int GetEndurance();
	int GetIntelligence();
	int GetHealthPoints();
	int GetHealthLimit();
	int GetManaPoints();
	int GetManaLimit();
	int GetExperience();
	int GetLevel();

	//methods for levelling up
	void IncrementAttack();
	void IncrementDefence();
	void IncrementEndurance();
	void IncrementIntelligence();

	void SetAttack(int val);
	void SetDefense(int val);
	void SetHealth(int val);
	void SetMana(int val);
	void SetHealthLimit();
	void SetManaLimit();
	void SetExperience(int val);
	void GainExperience(int DungeonLevel);
	void GainLevel();
	void SetState(Effect effect, int duration);

	//
	void CheckState();

	void UseHealthPotion();
	void UseManaPotion();
	void DisplaySkills();

	//Method for applying skill's effects
	void ExecuteSkill(int skill, Character * target);

	//Method for choosing skill based on mouse input
	int ChooseSkill();

	Effect GetCurrentState();

	//Virtual method for creating character's skillset
	virtual void InitializeSkillset() = 0;

	//Virtual method for drawing character's sprite on fight screen
	virtual void DisplaySprite(sf::RenderWindow * window) = 0;
};

#endif
#include "Character.h"

void Character::Attack(Character * target)
{
	int power = 20 * this->attack / target->defence;
	target->SetHealth(target->GetHealthPoints() - power);
}

std::vector<int> Character::getStats()
{
	std::vector<int> stats;
	stats.push_back(attack);
	stats.push_back(defence);
	stats.push_back(endurance);
	stats.push_back(intelligence);
	stats.push_back(hp);
	stats.push_back(mana);
	stats.push_back(hp_limit);
	stats.push_back(mana_limit);
	stats.push_back(red_potions);
	stats.push_back(blue_potions);
	return stats;
}

int Character::GetAttack()
{
	return this->attack;
}

int Character::GetDefence()
{
	return this->defence;
}

int Character::GetHealthPoints()
{
	return this->hp;
}

int Character::GetHealthLimit()
{
	return this->hp_limit;
}

int Character::GetManaPoints()
{
	return this->mana;
}

int Character::GetManaLimit()
{
	return this->mana_limit;
}

int Character::GetEndurance()
{
	return this->endurance;
}

int Character::GetIntelligence()
{
	return this->intelligence;
}

int Character::GetExperience()
{
	return this->experience;
}

int Character::GetLevel()
{
	return this->level;
}

void Character::IncrementAttack()
{
	attack++;
}

void Character::IncrementDefence()
{
	defence++;
}

void Character::IncrementEndurance()
{
	endurance++;
}

void Character::IncrementIntelligence()
{
	intelligence++;
}

void Character::SetAttack(int val)
{
	this->attack = val;
}

void Character::SetDefense(int val)
{
	this->defence = val;
}

void Character::SetHealth(int val)
{
	this->hp = val;
}

void Character::SetMana(int val)
{
	this->mana = val;
}

void Character::SetHealthLimit()
{
	this->hp_limit = this->GetEndurance()*10;
}

void Character::SetManaLimit()
{
	this->mana_limit = this->GetIntelligence()*10;
}

void Character::SetExperience(int val)
{
	this->experience = val;
}

void Character::GainExperience(int DungeonLevel)
{
	experience += 100 * DungeonLevel / level;
}

void Character::GainLevel()
{
	level++;
}

void Character::UseHealthPotion()
{
	if (red_potions == 0)
	{
		throw std::logic_error("No red potions!");
	}
	else
	{
		red_potions--;
		this->SetHealth(this->GetHealthLimit());
	}
}

void Character::UseManaPotion()
{
	if (blue_potions == 0)
	{
		throw std::logic_error("No blue potions!");
	}
	else
	{
		blue_potions--;
		this->SetMana(this->GetManaLimit());
	}
}

void Character::DisplaySkills()
{
	for (int i = 0; i < 3; i++)
	{
		skillset[i].DisplayIcon();
	}
}

void Character::SetState(Effect effect, int duration)
{
	currentState = effect;
	state_duration = duration;
}

void Character::CheckState()
{
	if (currentState != CLEAN)
	{
		state_duration--;
		if (state_duration == 0)
		{
			switch (currentState)
			{
			case RAISE_ATTACK:
				SetAttack(GetAttack() - temp);
				break;
			case RAISE_DEFENCE:
				SetDefense(GetDefence() - temp);
				break;
			default:
				break;
			}
			currentState = CLEAN;
			temp = 0;
		}
	}
}


void Character::ExecuteSkill(int skill, Character * target)
{
	Effect * effects = skillset[skill].GetEffects();
	int power = skillset[skill].GetPower();
	if (this->GetManaPoints() < (power * 25))
	{
		throw std::logic_error("Not enough mana!");
	}
	
	for (int i = 0; i < 2; i++)
	{
		switch (effects[i])
		{
		case DEAL_DAMAGE:
			target->SetHealth(target->GetHealthPoints() - (2 * power*intelligence));
			break;
		case STUN:
			target->SetState(STUN, power + 1);
			break;
		case RAISE_ATTACK:
			this->SetState(RAISE_ATTACK, power + 1);
			this->temp += 3 + intelligence / 4;
			this->SetAttack(this->GetAttack() + temp);
			break;
		case RAISE_DEFENCE:
			this->SetState(RAISE_DEFENCE, power + 1);
			this->temp = 3 + intelligence / 4;
			this->SetDefense(this->GetDefence() + temp);
			break;
		case HEAL:
			this->SetHealth(GetHealthPoints() + 2 * power * intelligence);
			if (GetHealthPoints() > GetHealthLimit())
			{
				SetHealth(GetHealthLimit());
			}
			break;
		case GRANT_IMMUNITY:
			this->SetState(GRANT_IMMUNITY, power + 1);
			break;
		case CLEAN:
			break;
	}
}
	SetMana(GetManaPoints() - 25 * power);
}

int Character::ChooseSkill()
{
	int xOffset = window->getPosition().x;
	int yOffset = window->getPosition().y;
	sf::Vector2i mp = sf::Mouse::getPosition();
	sf::Vector2f first = skillset[0].GetIconPosition();
	sf::Vector2f second = skillset[1].GetIconPosition();
	sf::Vector2f third = skillset[2].GetIconPosition();

	if (mp.y > first.y + yOffset + 30 && mp.y < first.y + yOffset + 90)
	{
		if (mp.x > first.x + xOffset && mp.x < first.x + xOffset + 80)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					sf::sleep(sf::microseconds(5));
				}
				return 0;
			}
		}
		else if (mp.x > second.x + xOffset && mp.x < second.x + xOffset + 80)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					sf::sleep(sf::microseconds(5));
				}
				return 1;
			}
		}
		else if (mp.x > third.x + xOffset && mp.x < third.x + xOffset + 80)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					sf::sleep(sf::microseconds(5));
				}
				return 2;
			}
		}
	}
	return -1;
}

Effect Character::GetCurrentState()
{
	return currentState;
}

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Character.h"
#include "Knight.h"
#include "Priestess.h"
#include "Barbarian.h"
#include "Witch.h"
#include "Enemy.h"
#include "LevelUpBox.h"

typedef enum Direction { DOWN, RIGHT, UP, LEFT, NONE };

struct MapSprite
{
	MapSprite();
	MapSprite(int choice);
	
	int x;
	int y;
	int TextureYOffset;

	sf::Texture texture;
	sf::RectangleShape sprite;
	sf::Vector2u textureSize;
	Direction direction;
};

class GameEngine
{
	bool encounter;
	int choice;
	int DungeonLevel;
	Character * hero;
	MapSprite mapSprite;
	sf::RenderWindow * window;
	sf::Event event_;
	sf::Texture DungeonBackground;
	sf::Texture FightBackground;
	sf::RectangleShape FightScreen;
	sf::RectangleShape Background;
public:
	GameEngine(sf::RenderWindow * window_, int choice, Character * character);
	virtual ~GameEngine();

	//Engine's main method
	void Run();

	void DisplayMap();
	void DrawHero();
	void MoveHero();

	//Based on mapSprite's position returns
	//the direction from which it's blocked
	Direction CheckMapBoundaries();
	void ExitRoom();
	int UseSkill(Character * e);

	//Draws potential encounter every time
	//the hero moves on the map, returns true
	//if the encounter is to happen
	bool RollEncounter();

	//Initializes and runs the encounter
	//Returns true if the hero prevails or runs,
	//returns false if hero dies
	bool TriggerEncounter();

	//Function for choosing action in fight
	//based on mouse input
	int ChooseAction(sf::Text a, sf::Text s, sf::Text r, sf::Text h, sf::Text m);
	void DisplayMapStats();

	void LevelUp();
	
	void WriteCharacterCurrentStats(Character * character, bool offset);

	void DisplayFightScreen();

	Character * GetHeroPointer();
};

#endif
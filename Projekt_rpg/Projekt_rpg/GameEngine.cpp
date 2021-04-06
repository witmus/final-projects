#include "GameEngine.h"

MapSprite::MapSprite() {}

MapSprite::MapSprite(int choice) :sprite(sf::Vector2f(50, 65))
{
	direction = UP;
	x = 615;
	y = 890;
	TextureYOffset = choice - 1;
	texture.loadFromFile("../Textures/map_sprites_final.png");
	textureSize = texture.getSize();
	textureSize.x /= 4;
	textureSize.y /= 4;
	sprite.setTexture(&texture);
	sprite.setTextureRect(sf::IntRect(textureSize.x * direction, textureSize.y * TextureYOffset, textureSize.x, textureSize.y));
	sprite.setPosition(sf::Vector2f(x, y));
}

GameEngine::GameEngine(sf::RenderWindow * window_, int choice_, Character * character) :window(window_), Background(sf::Vector2f(1280, 960)), FightScreen(sf::Vector2f(1280, 960)),mapSprite(choice_), hero(character)
{
	encounter = false;
	choice = choice_;
	DungeonLevel = 1;
	DungeonBackground.loadFromFile("../Textures/dungeon.png");
	FightBackground.loadFromFile("../Textures/fight_screen.png");
	Background.setTexture(&DungeonBackground);
	FightScreen.setTexture(&FightBackground);
}

GameEngine::~GameEngine()
{
}

void GameEngine::DisplayMap()
{
	this->window->draw(Background);
}

void GameEngine::DrawHero()
{
	//mapSprite.sprite.setPosition(sf::Vector2f(615, 1205));
	mapSprite.sprite.setTextureRect(sf::IntRect(mapSprite.textureSize.x * mapSprite.direction, mapSprite.textureSize.y * mapSprite.TextureYOffset, mapSprite.textureSize.x, mapSprite.textureSize.y));
	this->window->draw(mapSprite.sprite);
}

Direction GameEngine::CheckMapBoundaries()
{
	if (mapSprite.sprite.getPosition().x < 350)
	{
		return LEFT;
	}
	else if ( mapSprite.sprite.getPosition().x > 900)
	{
		return RIGHT;
	}
	else if (mapSprite.sprite.getPosition().y > 870)
	{
		return DOWN;
	}
	else return NONE;
}

void GameEngine::MoveHero()
{
	Direction block = CheckMapBoundaries();
	
	sf::Time sleepTime = sf::microseconds(1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		mapSprite.sprite.move(sf::Vector2f(0, -mapSprite.sprite.getSize().y));
		mapSprite.direction = UP;
		encounter = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && block != DOWN)
	{
		mapSprite.sprite.move(sf::Vector2f(0, mapSprite.sprite.getSize().y));
		mapSprite.direction = DOWN;
		encounter = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && block != LEFT)
	{
		mapSprite.sprite.move(sf::Vector2f(-mapSprite.sprite.getSize().x, 0));
		mapSprite.direction = LEFT;
		encounter = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && block != RIGHT)
	{
		mapSprite.sprite.move(sf::Vector2f(mapSprite.sprite.getSize().x, 0));
		mapSprite.direction = RIGHT;
		encounter = true;
	}
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		sf::sleep(sleepTime);
	}
}

void GameEngine::DisplayMapStats()
{
	sf::Font font;
	font.loadFromFile("ink-free-normal.ttf");
	sf::Text text("", font);
	text.setCharacterSize(36);
	text.setPosition(sf::Vector2f(250, -10));
	text.setLineSpacing(1.2);
	text.setString(std::to_string(hero->GetLevel()) + '\n' + std::to_string(DungeonLevel) + '\n' + std::to_string(hero->GetExperience()));
	window->draw(text);
}

void GameEngine::ExitRoom()
{
	mapSprite.sprite.setPosition(sf::Vector2f(615, 890));
	DungeonLevel++;
}

bool GameEngine::RollEncounter()
{
	srand(time(NULL));
	int roll = rand() % 100;
	if (roll % 3 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Character * GameEngine::GetHeroPointer()
{
	return this->hero;
}

void GameEngine::WriteCharacterCurrentStats(Character * character, bool offset)
{
	std::vector<int> stats = character->getStats();
	std::vector<std::string> stats_string;

	sf::Font font;
	font.loadFromFile("ink-free-normal.ttf");
	std::vector<sf::Text> text_array;

	for (int i = 0; i < 6; i++)
	{
		stats_string.push_back(std::to_string(stats[i]));
		text_array.push_back(sf::Text(stats_string[i], font));
		text_array[i].setPosition(sf::Vector2f(130 + 970 * offset, 70 * (i + 1)));
		text_array[i].setCharacterSize(36);
		this->window->draw(text_array[i]);
	}
}

void GameEngine::DisplayFightScreen()
{
	window->draw(FightScreen);
}



int GameEngine::ChooseAction(sf::Text a, sf::Text s, sf::Text r, sf::Text h, sf::Text m)
{
	int action = 0;
	sf::Time sleepTime = sf::microseconds(1);
	int height = a.getLocalBounds().height;
	float widthA = a.getLocalBounds().width;
	float widthS = s.getLocalBounds().width;
	float widthR = r.getLocalBounds().width;
	float widthH = h.getLocalBounds().width;
	float widthM = m.getLocalBounds().width;
	float windowOffsetX = window->getPosition().x;
	float windowOffsetY = window->getPosition().y;
	float MouseX = sf::Mouse::getPosition().x;
	float MouseY = sf::Mouse::getPosition().y;

	if (MouseY > a.getPosition().y + windowOffsetY + height && MouseY < a.getPosition().y + height + height + windowOffsetY)
	{
		if (MouseX > a.getPosition().x + windowOffsetX && MouseX < a.getPosition().x + windowOffsetX + widthA)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				action = 1;
			}
		}
		else if (MouseX > s.getPosition().x + windowOffsetX && MouseX < s.getPosition().x + widthS + windowOffsetX)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				action = 2;
			}
		}
		else if (MouseX > r.getPosition().x + windowOffsetX && MouseX < r.getPosition().x + windowOffsetX + widthR)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				action = 3;
			}
		}
	}
	else if (MouseY > h.getPosition().y + windowOffsetY + height && MouseY < h.getPosition().y + height + height + windowOffsetY)
	{
		if (MouseX > h.getPosition().x + windowOffsetX && MouseX < h.getPosition().x + windowOffsetX + widthH)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				action = 4;
			}
		}
		else if (MouseX > m.getPosition().x + windowOffsetX && MouseX < m.getPosition().x + widthM + windowOffsetX)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				action = 5;
			}
		}
	}
	while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::sleep(sleepTime);
	}
	return action;
}

void GameEngine::LevelUp()
{
	hero->GainLevel();
	LevelUpBox LvlBox(window, hero);
	LvlBox.RunBox();
}

int GameEngine::UseSkill(Character * e)
{
	int choice = 0;
	while (window->isOpen())
	{
		window->clear();
		DisplayFightScreen();
		hero->DisplaySprite(window);
		hero->DisplaySkills();
		e->DisplaySprite(window);
		WriteCharacterCurrentStats(hero, false);
		WriteCharacterCurrentStats(e, true);
		choice = hero->ChooseSkill();
		if (choice != -1)
		{
			return choice;
		}
		window->display();
	}
	return -1;
}

bool GameEngine::TriggerEncounter()
{
	int action;
	int skill;

	sf::Font font;
	font.loadFromFile("ink-free-normal.ttf");
	sf::Text AttackBox("Attack", font);
	sf::Text SkillBox("Use skill", font);
	sf::Text RunBox("Run", font);
	sf::Text Health("Use health potion", font);
	sf::Text Mana("Use mana potion", font);
	AttackBox.setCharacterSize(64);
	SkillBox.setCharacterSize(64);
	RunBox.setCharacterSize(64);
	Health.setCharacterSize(64);
	Mana.setCharacterSize(64);
	AttackBox.setPosition(sf::Vector2f(100, 550));
	SkillBox.setPosition(sf::Vector2f(550, 550));
	RunBox.setPosition(sf::Vector2f(1000, 550));
	Health.setPosition(sf::Vector2f(100, 750));
	Mana.setPosition(sf::Vector2f(700, 750));

	Enemy skeleton(DungeonLevel);
	Character * enemy = &skeleton;
	while (window->isOpen())
	{
		window->clear();
		DisplayFightScreen();
		hero->DisplaySprite(window);
		enemy->DisplaySprite(window);
		window->draw(AttackBox);
		window->draw(SkillBox);
		window->draw(RunBox);
		window->draw(Health);
		window->draw(Mana);
		action = ChooseAction(AttackBox, SkillBox, RunBox, Health, Mana);
		WriteCharacterCurrentStats(hero, false);
		WriteCharacterCurrentStats(enemy, true);
		switch (action)
		{
		case 1:
			hero->Attack(enemy);
			break;
		case 2:
			skill = UseSkill(enemy);
			if (skill != -1)
			{
				try {
					hero->ExecuteSkill(skill, enemy);
				}
				catch (std::logic_error & e) {
					std::cout << "Not enough mana!\n";
					action = 0;
				}
			}
			break;
		case 3:
			return true;
		case 4:
			try {
				hero->UseHealthPotion();
			}
			catch (std::logic_error & e) {
				std::cout << "No red potions\n";
				action = 0;
			}
			break;
		case 5:
			try {
				hero->UseManaPotion();
			}
			catch (std::logic_error & e) {
				std::cout << "No blue potions\n";
				action = 0;
			}
			break;
		case 0:
			break;
		}
		if (enemy->GetHealthPoints() <= 0)
		{
			hero->GainExperience(DungeonLevel);
			if (hero->GetExperience() >= 100)
			{
				hero->SetExperience(hero->GetExperience() - 100);
				LevelUp();
			}
			return true;
		}
		if (action)
		{
			if (hero->GetCurrentState() != GRANT_IMMUNITY && enemy->GetCurrentState() != STUN)
			{
				enemy->Attack(hero);
				if (hero->GetHealthPoints() <= 0)
				{
					return false;
				}
			}
			hero->CheckState();
			enemy->CheckState();
		}
		
		window->display();
	}
}


void GameEngine::Run()
{
	if (hero == nullptr) return;
	sf::Time sleepTime = sf::microseconds(15);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				return;
			}
		}
		window->clear();
		DisplayMap();
		DrawHero();
		DisplayMapStats();
		window->display();
		if (sf::Keyboard::isKeyPressed)
		{
			if (RollEncounter() && encounter)
			{
				sf::sleep(sleepTime);
				if (!TriggerEncounter())
				{
					std::cout << "YOU DIED\n";
					return;
				}
				
				encounter = false;
			}
			MoveHero();
			if (mapSprite.sprite.getPosition().y < 10)
			{
				ExitRoom();
			}
		}
	}
}
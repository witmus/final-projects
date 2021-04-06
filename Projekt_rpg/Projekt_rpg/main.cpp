#include "Header.h"
#include "GameEngine.h"

int main()
{
	sf::Music music;
	music.openFromFile("gm1.wav");
	music.play();
	music.setLoop(true);
	sf::RenderWindow window(sf::VideoMode(1280, 960), "D&S", sf::Style::Close | sf::Style::Titlebar);
	window.setKeyRepeatEnabled(false);
	DisplayStartScreen(&window);
	while (window.isOpen())
	{
		sf::Event event;


		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			window.clear();
			break;
		}
	}
	int CharacterSelection = DisplayClassSelection(&window);
	Knight k(&window);
	Priestess p(&window);
	Barbarian b(&window);
	Witch w(&window);
	Character * hero;
	switch(CharacterSelection)
	{
	case 1:
		hero = &k;
		break;
	case 2:
		hero = &p;
		break;
	case 3:
		hero = &b;
		break;
	case 4:
		hero = &w;
		break;
	default:
		hero = nullptr;

	}
	hero->InitializeSkillset();
	GameEngine engine(&window, CharacterSelection, hero);
	engine.Run();
	music.setLoop(false);
	return 0;
}
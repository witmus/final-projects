#pragma once

#include <iostream>
#include <ctime>
#include <stdexcept>
#include <crtdbg.h>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

//Main menu methods
void DisplayStartScreen(sf::RenderWindow * window);
int DisplayClassSelection(sf::RenderWindow * window);
void WriteCharacterDescription(char charClass, sf::RenderWindow * window);
int DisplayClassCharacteristics(sf::RenderWindow * window, sf::RectangleShape * Portraits);
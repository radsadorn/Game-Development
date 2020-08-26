#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Button.h"

#include "ctime"
#include "cstdlib"
#include "fstream"
#include "sstream"
#include "stack"
#include "map"

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	~PauseMenu();

	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonsPressed(const std::string key) ;
	void addButton(sf::Texture* texture, const std::string key, float line, int y, const std::string text);
	void updatePosition(float x, float y, float z);
	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

private:
	sf::Font& font;
	sf::Text menuText;

	sf::Texture buttonTexture;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

};


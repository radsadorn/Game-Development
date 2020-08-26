#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Button.h"
#include "FadeStates.h"

#include "ctime"
#include "cstdlib"
#include "fstream"
#include "sstream"
#include "stack"
#include "map"

class GameWin
{
public:
	GameWin(sf::RenderWindow& window, sf::Font& font, std::string state, std::string namePlayer, int score, bool endgame);
	~GameWin();

	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonsPressed(const std::string key);
	void addButton(sf::Texture* texture, const std::string key, float line, int n, int m, const std::string text);
	void updatePosition(sf::Vector2f pos, sf::Vector2f size);
	void updateScore();
	void update(sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

private:
	sf::Font& font;

	sf::Text win;
	sf::Text namePlayer;
	sf::Text score;

	int point;
	int pointUpdate = 0;
	bool endgame;

	std::map<std::string, gui::Button*> buttons;

	sf::Texture buttonTexture;

};


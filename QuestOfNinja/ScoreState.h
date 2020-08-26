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

class ScoreState
{
public:
	ScoreState(sf::RenderWindow& window, sf::Font& font);
	~ScoreState();

	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonsPressed(const std::string key);
	void addButton(const std::string key, float line, int n, const std::string text);
	void updatePosition(float x, float y, sf::Vector2f size);
	void updateHighScore();
	void update(sf::Vector2f& mousePos);
	void renderScore(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

	void initVeriables();

private:
	sf::Font& font;
	sf::Text menuText;
	sf::Clock clock;

	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::RectangleShape paper;

	sf::Texture buttonTexture;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, int> highscore;
	sf::Text scoreName[5];
	sf::Text scorePoint[5];

	sf::Texture hokangeTexture;
	sf::RectangleShape hokange;

	//Variables
	int countLine = -1;
	int countText = 0;
	float totalTime = 0;
	std::string bar ;
	std::string text = "LEADER-BOARD";

	void initHighScore();
	void initScoreBar();
	
};


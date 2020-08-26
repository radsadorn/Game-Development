#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "iostream"

#include "ctime"
#include "cstdlib"
#include "fstream"
#include "sstream"
#include "stack"
#include "map"

#include "windows.h"
#include "time.h"

class State
{
private:
	float VIEW_HEIGHT = 1082 * 0.7;
	float VIEW_WIDTH = 1920 * 0.7;

protected:
	std::stack <State*>* states;

	sf::RenderWindow* window;
	sf::View view;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int>* keybins;
	bool quit = false;
	bool pause = false;
	bool highScore = false;
	bool howtoplay = false;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> texture;

	//Name player
	std::string namePlayer = "";

	//Name Random
	int name;
	std::vector <std::string> nameRandom;

	//Endgame
	bool win = false;

	//High Score
	std::vector <std::string> scoreName;
	std::vector <int> scorePoint;

	//Function
	void initView();
	void initNameRandom();

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void endStates();
	void pauseState();
	void unpauseState();
	void highscoreState();
	void unhighscoreState();
	void howtoplayState();
	void unhowtoplayState();

	virtual void updateMousePositions();
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime, sf::Event sfEven) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;

};


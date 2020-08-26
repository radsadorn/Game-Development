#pragma once

#include "GameStates.h"
#include "MainMenuState.h"

class GameMain
{
public:
	GameMain();
	~GameMain();


	void endGame();
	void updateSFMLEvent();
	void update();

	void render();

	void run();

private:
	void initVariable();
	void initwindow();
	void initKey();
	void initStates();

	sf::RenderWindow* window;

	sf::Event sfEvent;

	std::vector<sf::VideoMode> VideoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	std::stack <State*> states;

	std::map<std::string, int> supportedKeys;


	float deltaTime;

};


#pragma once

#include "NameState.h"
#include "ScoreState.h"
#include "HowState.h"

class MainMenuState :
	public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states);
	~MainMenuState();

	//Function
	void updateInput(const float& deltaTime);
	void update(const float& deltaTime, sf::Event sfEven);
	void updateBackButton();
	void updateButtons();
	void render(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget& target);

private:
	ScoreState* scoreBack;
	HowState* howBack;

	sf::Music music;

	//Variable
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Texture LOGO;
	sf::RectangleShape logo;

	//sf::Texture buttonTexture;
	sf::Font font;
	sf::Font mefont;
	sf::Text name;
	sf::Text me;

	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, sf::Texture> buttonTexture;

	gui::Button* gamestate_btn;

	//Function
	void initVariable();
	void initBackground();
	void initFonts();
	void initHowtoPlay();
	void initKeybins();
	void initButton();
	void initHighScore();
	void initName();
};


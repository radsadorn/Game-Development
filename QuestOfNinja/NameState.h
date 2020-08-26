#pragma once

#include "GameStates.h"
#include "Animation.h"

class NameState :
	public State
{
public:
	NameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states, sf::Music& music);
	virtual ~NameState();

	std::string getNamePlayer() { return this->namePlayer; };

	void updateDelta();
	void updateInput(const float& deltaTime);
	void update(const float& deltaTime, sf::Event sfEven);
	void updateButtons();
	void updateNameBox(sf::Event sfEven);
	void render(sf::RenderTarget* target = NULL);
	void renderButtons(sf::RenderTarget& target);
	void renderCursor(sf::RenderTarget& target);

private:
	sf::RectangleShape body;
	Animation* player;

	sf::Music& music;

	sf::Texture nameboxTexture;
	std::map<std::string, sf::Texture> buttonTexture;

	sf::RectangleShape nameBox;
	sf::RectangleShape cursor;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	sf::Texture loadingTexture;
	sf::RectangleShape loadingBackground;

	sf::Font font;
	sf::Clock clock;

	sf::Clock deleteTime;
	float totaltimedelete = 0;

	std::map<std::string, gui::Button*> buttons;
	float deltaTime = 0.0f;
	const float Scale = 1.5f;

	//Name Box
	float totalTime = 0.f;
	sf::Clock time;
	bool state = false;
	char last_char = ' ';
	sf::Font nameFont;
	sf::Text text;
	sf::Text nameBG;

	//Loading
	sf::RectangleShape loading;
	sf::Text loadingText;
	int fade = 0;
	bool load = false;
	bool loadingFinish = false;

	void initTextures();
	void initPlayer();
	void initKeybins();
	void initFont();
	void initBackground();
	void initNameText();
	void initButtons();
	void initNameBox();
	void initLoading();
};


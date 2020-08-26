#pragma once


#include "State.h"
#include "Button.h"

class WindowGameState
	: public State
{
public:
	WindowGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states, sf::Font& font);
	~WindowGameState();

	void updatePowerUp();
	void updateScorBar();
	void updateHPbar();
	void updateBagItems();
	void updateMana();
	void updateHP();
	void updateCountdown_skill(int st, int nd, int rd);
	void updateButtonInput();
	void updatePositionWindowGame();
	void renderWindowGameState(sf::RenderTarget* target);

private:
	std::vector <std::string> buttonname;
	sf::Font& font;

	void initTextures();
	void initButtons();
	void initLockSkill();
	void initBagButton();
	void initHPBar();
	void initScoreBar();
	void initCountdown_skill();

protected:
	//Score
	int score = 0;
	sf::Text scoreText;
	bool write = false;

	//HP
	int HP = 10000;
	sf::Text HPbar;
	sf::Text ManaBar;

	//Mana
	int MANA = 100;
	sf::Clock manaClock;
	float manaTime = 0;

	bool start = true;

	//BAG
	sf::Text countItemsText[2];
	int countItems[2] = {};

	//Bar
	sf::RectangleShape hpbarshape;
	sf::CircleShape profile;
	sf::CircleShape playerProfile;

	sf::RectangleShape heart;
	sf::RectangleShape mana;

	sf::RectangleShape hpStatus;
	sf::RectangleShape hpBG;
	sf::RectangleShape manaStatus;
	sf::RectangleShape manaBG;
	sf::CircleShape hpEnd;
	sf::CircleShape manaEnd;
	sf::CircleShape hpEndBG;
	sf::CircleShape manaEndBG;

	sf::Texture howTexture;
	sf::RectangleShape how;

	sf::RectangleShape nameBox;

	sf::RectangleShape fistRec;

	//Countdown
	sf::Text countdown_skill[3];

	sf::RectangleShape colldownskill[3];
	//States
	int states = 1;

	//Texture
	std::map<std::string, sf::Texture> texture;

	//Button
	std::map<std::string, gui::Button*> buttons;

	gui::Button* howbutton;

	//Keep Items
	sf::Clock itemClock;
	float totalKeepItemsTime = 0.f;
	int itemsCount = 0;

	//Power 
	int power = 2;
	std::vector <float> totaltimepowerup;
	sf::Clock clockpower;
	sf::Text powerText;
	bool powerup = false;
};


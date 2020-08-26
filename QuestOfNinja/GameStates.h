#pragma once

#include "WindowGameState.h"

#include "Platform.h"
#include "Body.h"
#include "PauseMenu.h"
#include "ScoreState.h"
#include "LoopBackground.h"
#include "Monster.h"
#include "HitboxComponent.h"
#include "NameState.h"
#include "GameWin.h"
#include "Item.h"

#include "Boss.h"

#include "ThrowingState.h"

#include "iostream"
#include "map"

class GameStates :
	public WindowGameState
{
public:
	GameStates(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states, std::string namePlayer, sf::Music& music);
	virtual ~GameStates();

	//Function
	void updateInput(const float& deltaTime);
	void updatePauseInput(const float& deltaTime);

	void updateDelta();

	void updateBackground(const float& deltaTime);

	void updatePauseMenuButtons();
	void updateBackButton();

	void updateKeepItems(Platform& platform, const float& deltaTime);
	void updatePickup(Item& item);
	
	void UpdateAttack(sf::Event sfEvent);
	void throwItem();

	void updateBoss();

	void updateGamewin();

	void update(const float& deltaTime, sf::Event sfEven);


	void renderBackground(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);

private:
	//Menu
	PauseMenu* pmenu;
	ScoreState* scoreBack;
	GameWin* gamewin;

	//Player
	Body* player;
	HitboxComponent* sword;
	sf::Vector2f direction;
	float deltaTime = 0.0f;

	//Monster
	std::vector <Monster*> golem;

	//Boss
	std::vector <Boss*> boss;
	bool seeBoss = false;
	sf::Clock clockBoss;
	float totaltimeboss = 0;

	//Attack
	float hit;
	char last_char = ' ';

	//Background
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	std::vector <Platform> platforms;

	sf::Texture block1;
	sf::Texture block2;

	sf::Texture loadingTexture;
	sf::RectangleShape loadingBackground;
	sf::Text loading;

	//Item
	std::vector <sf::Texture> itemTexture;
	std::vector <Item*> items;

	
	//End game
	sf::RectangleShape fadeBox;
	int fade = 0;

	//Object
	sf::Music music;
	sf::Clock clock;
	sf::Font font;
	sf::Vector2f size;

	//Key
	std::map<std::string, int> keybins;
	std::map<std::string, sf::Texture> BackgroundTexture;
	std::map<std::string, LoopBackground*> Background;

	//Start
	bool state = false;
	bool start = false;
	bool change = false;
	sf::RectangleShape startBox;
	int fadeStart = 255;
	sf::Clock clockstart;
	float totalTimeStart = 0;

	//State
	bool endThisState = false;

	//Throwing
	sf::Texture itemTextureMain;
	std::vector <ThrowingState*> throwItems;
	sf::Clock clockItem; 
	float totaltimeuseitem = 0.f;


	//Function 
	void startState();

	void initKeybins();

	void initChangeState();

	void initTextures();
	void initPlayer();
	void initMonster();

	void initPauseMenu();

	void initBackground();
	void initPlatform();

	void initItems();

	void initMusic();
	void initFonts();
	void initHighScore();
	void initGameWin(std::string state, bool endgame);
};

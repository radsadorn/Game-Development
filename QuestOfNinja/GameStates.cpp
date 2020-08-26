#include "GameStates.h"

void GameStates::startState()
{
	this->startBox.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
	this->startBox.setOrigin(sf::Vector2f(this->startBox.getSize().x / 2, 0));
	this->startBox.setPosition(sf::Vector2f(this->view.getCenter().x, 0-(this->window->getSize().y / 2.f)));
	this->startBox.setFillColor(sf::Color(0, 0, 0, 255));
}

void GameStates::initKeybins()
{ 
	std::ifstream ifs("config/gamestates_keybins.ini");

	if (ifs.is_open())
	{
		std::string key1 = "";
		std::string key2 = "";

		while (ifs >> key1 >> key2)
		{
			this->keybins[key1] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();
}

void GameStates::initChangeState()
{
	this->loadingTexture.loadFromFile("background/LOADING.png");
	this->loadingTexture.setSmooth(true);
	this->loadingBackground.setTexture(&this->loadingTexture);

	this->loadingBackground.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().y * 1915 / 1072),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->loadingBackground.setOrigin(sf::Vector2f(this->loadingBackground.getSize().x / 2, 0));
	this->loadingBackground.setPosition(sf::Vector2f(this->view.getCenter().x, 0 - (this->window->getSize().y / 2.f)));

	this->loading.setFont(this->font);
	this->loading.setString("PRESS SPACE TO START");
	this->loading.setCharacterSize(40);
	this->loading.setFillColor(sf::Color::White);
	this->loading.setLetterSpacing(1);
	this->loading.setOrigin(sf::Vector2f(this->loading.getGlobalBounds().width / 2, this->loading.getGlobalBounds().height / 2));
	this->loading.setPosition(sf::Vector2f(0, this->window->getSize().y / 7 * 3));
}

//Characters
void GameStates::initTextures()
{
	this->texture["PLAYER_IDLE"].loadFromFile("sprite/allSprite.png");
	this->texture["PLAYER_IDLE"].setSmooth(true);

	this->itemTextureMain.loadFromFile("items/ITEM.png");
	this->itemTextureMain.setSmooth(true);
}

void GameStates::initPlayer()
{
	this->player = new Body(&this->texture["PLAYER_IDLE"], sf::Vector2u(8, 9), 0.1f, 100.0f, 280.0f);
	this->sword = new HitboxComponent(sf::Vector2f(1000, 300), sf::Vector2f(180, 80));
}

void GameStates::initMonster()
{
	this->texture["GOLEM"].loadFromFile("sprite/GOLEM" + std::to_string(this->states) + ".png");
	this->texture["GOLEM"].setSmooth(true);

	this->texture["GOBLIN"].loadFromFile("sprite/GOBLIN" + std::to_string(this->states) + ".png");
	this->texture["GOBLIN"].setSmooth(true);

	/*this->texture["TROLL1"].loadFromFile("sprite/troll" + std::to_string(this->states) + ".png");
	this->texture["TROLL1"].setSmooth(true);*/

	while (!this->golem.empty())
	{
		this->golem.erase(this->golem.begin());
	}

	while (!this->boss.empty())
	{
		this->boss.erase(this->boss.begin());
	}

	for (int i = 0; i < 25; ++i)
	{
		int dis = (rand() % 10 + 10) * 4;
		int born = rand() % 8500;
		float speed = rand() % 30 + 130;
		int point = rand() % 20 + 90;
		int power = rand() % 20 + 20;
		if (!(born % 2))
		{
			this->golem.push_back(new Monster(
				&this->texture["GOLEM"],
				sf::Vector2f(born + 1500, 500),
				sf::Vector2u(12, 4),
				sf::Vector2f(225.f / 2, 225.f / 2),
				12, 0.07f, speed, dis, 300 * this->states + 100, point, power));
		}
	}

	for (int i = 0; i < 15; ++i)
	{
		int dis = (rand() % 10 + 10) * 4;
		int born = rand() % 5000;
		float speed = rand() % 30 + 150;
		int point = rand() % 40 + 180;
		int power = rand() % 20 + 60;
		if (!(born % 2))
		{
			this->golem.push_back(new Monster(
				&this->texture["GOBLIN"],
				sf::Vector2f(born + 7000, 500),
				sf::Vector2u(12, 4),
				sf::Vector2f(225.f / 2, 225.f / 2),
				12, 0.06f, speed, dis, 500 * this->states, point, power));
		}
	}

	int point = this->states * 1000;
	int power = this->states * 50;
	this->boss.push_back(new Boss(
		&this->texture["GOLEM"],
		sf::Vector2f(12900, 500),
		sf::Vector2u(12, 4),
		sf::Vector2f(225.f / 2, 225.f / 2),
		12, 0.07f, 200 + this->states * 10, 60, 3000 * this->states, point, power));


}

//Map
void GameStates::initBackground()
{
	this->size = sf::Vector2f(
		static_cast<float>(this->window->getSize().y * 1920 / 1080),
		static_cast<float>(this->window->getSize().y)
	);

	std::ifstream ifs("config/background.ini");

	if (ifs.is_open())
	{
		std::string name = "";
		float delta = 0.f;

		while (ifs >> name >> delta)
		{
			std::string file = "background/Cartoon_Forest_BG_0" + std::to_string(this->states) + "/Layers/" + name + ".png";
			this->BackgroundTexture[name].loadFromFile(file);
			this->Background[name] = new LoopBackground(&this->BackgroundTexture[name], this->size);
		}
	}
	ifs.close();

}

void GameStates::initPlatform()
{
	this->block1.loadFromFile("Object/FLOOR02_0" + std::to_string(this->states) + ".png");
	this->block1.setSmooth(true);
	this->block1.setRepeated(true);

	for (float i = 900; i < 12000; i += (rand() % 3 + (rand() % 3 + 4)) * 500)
		this->platforms.push_back(Platform(&this->block1, sf::Vector2f(418 * 0.6, 113 * 0.6), sf::Vector2f(i, float(this->window->getSize().y - 340.f))));
	for (float i = 500; i < 12000; i += (rand() % 4 + (rand() % 4 + 3)) * 300 )
		this->platforms.push_back(Platform(&this->block1, sf::Vector2f(418 * 0.6, 113 * 0.6), sf::Vector2f(i, float(this->window->getSize().y - 170.f))));

	this->block2.loadFromFile("Object/FLOOR01_0" + std::to_string(this->states) + ".png");
	this->block2.setSmooth(true);
	this->block2.setRepeated(true);
	for (float i = 0; i < 14000; i+=360)
		this->platforms.push_back(Platform(&this->block2, sf::Vector2f(418 * 0.9, 113 * 0.9), sf::Vector2f(i, float(this->window->getSize().y - 50.f))));
}

//Items
void GameStates::initItems()
{
	std::ifstream ifs("config/items.ini");

	if (ifs.is_open())
	{
		std::string name = "";

		while (ifs >> name)
		{
			sf::Texture items;
			items.loadFromFile("items/" + name + ".png");
			items.setSmooth(true);
			this->itemTexture.push_back(items);
			this->itemsCount++;
		}
	}
	ifs.close();

}

//Puase menu
void GameStates::initPauseMenu()
{
	this->pmenu = new PauseMenu(*window, font);

	this->pmenu->addButton(nullptr, "CONTINUE", this->window->getSize().y / 10.f, 3, "CONTINUE");
	this->pmenu->addButton(nullptr, "HIGH SCORE", this->window->getSize().y / 10.f, 5, "LEADER BOARD");
	this->pmenu->addButton(nullptr, "MAIN MENU", this->window->getSize().y / 10.f, 7, "MAIN MENU");
}

//Object
void GameStates::initMusic()
{
	this->music.openFromFile("map/NarutoBattleMusic.ogg");
	this->music.setLoop(true);
	this->music.setVolume(100);
}

void GameStates::initFonts()
{
	if (!this->font.loadFromFile("font/EDmuzazhi.ttf"))
		throw("ERROE::MAINMENUSTATE::COUND NOT LOAD FONT");
}

//Score
void GameStates::initHighScore()
{
	std::ifstream ifs("config/highscore.ini");

	if (ifs.is_open())
	{
		std::string name = "";
		int score = 0;

		while (ifs >> name >> score)
		{
			this->scoreName.push_back(name);
			this->scorePoint.push_back(score);
		}

	}

	ifs.close();

	this->scoreBack = new ScoreState(*this->window, this->font);
	this->scoreBack->addButton("BACK", this->window->getSize().y / 6.f, 5, "BACK");
}

//End game
void GameStates::initGameWin(std::string state, bool endgame)
{
	if (endgame)
	{
		std::ofstream text_Write("config/highscore.ini");
		if (text_Write.is_open())
		{
			for (int i = 0; i < 5; ++i)
			{
				if (this->score > this->scorePoint[i] and !this->write)
				{
					text_Write << this->namePlayer << " " << this->score << std::endl;
					this->write = !this->write;
				}

				text_Write << this->scoreName[i] << " " << this->scorePoint[i] << std::endl;

				if (this->score == this->scorePoint[i] and !this->write)
				{
					text_Write << this->namePlayer << " " << this->score << std::endl;
					this->write = !this->write;
				}
			}
		}
		text_Write.close();
	}

	this->fadeBox.setPosition(sf::Vector2f(this->Background["Sky"]->getPosition().x + this->window->getSize().x/ 2.f, this->window->getSize().y / 2.f));

	this->gamewin = new GameWin(*window, font, state, this->namePlayer, this->score, endgame);

	this->gamewin->updatePosition(this->fadeBox.getPosition(), this->fadeBox.getSize());

	this->gamewin->addButton(nullptr, "MAIN MENU", this->window->getSize().y / 6.f, 5, 0, "");
}

//Main 
GameStates::GameStates(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states, std::string namePlayer, sf::Music& music) :
	WindowGameState(window, supportedKeys, states, this->font)
{
	this->initView();

	this->initChangeState();

	this->initTextures();
	this->initPlayer();
	this->initMonster();

	this->initBackground();
	this->initPlatform();

	this->initItems();

	this->initMusic();
	this->initFonts();

	this->initPauseMenu();

	this->initHighScore();

	this->startState();

	this->fadeBox.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->fadeBox.setOrigin(this->fadeBox.getSize() / 2.f);

	this->namePlayer = namePlayer;
	this->music.play();
	music.pause();
}

GameStates::~GameStates()
{
	delete this->pmenu;
	delete this->player;
	delete this->scoreBack;

	for (auto& i : this->golem)
		delete i;

	for (auto& i : this->Background)
		delete i.second;

	while (!this->scoreName.empty())
	{
		this->scoreName.erase(this->scoreName.begin());
		this->scorePoint.erase(this->scorePoint.begin());
	}

	for (auto& item : this->items)
		delete item;
}

//Update delta
void GameStates::updateDelta()
{
	//Updates the delta variable with the time it takes to update and render one frame.
	this->deltaTime = this->clock.restart().asSeconds();

	if (this->deltaTime >= 1.0f / 20.0f)
		this->deltaTime = 1.0f / 20.0f;
}

//Update input
void GameStates::updatePauseInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) and !this->howtoplay)
	{
		if (!this->pause )
		{
			//this->music.pause();
			this->pauseState();
		}
		if (!this->highScore)
		{
			//this->music.pause();
			this->pauseState();
		}
	}
}

void GameStates::updateInput(const float& deltaTime)
{
	this->updateButtonInput();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		if (music.getVolume() == 0)
			music.setVolume(100);
		else music.setVolume(0);

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		if (!this->change)
		{
			this->change = true;
			this->start = true;
		}*/
}

//Update background
void GameStates::updateBackground(const float& deltaTime)
{
	std::ifstream ifs("config/background.ini");

	if (ifs.is_open())
	{
		std::string name = "";
		float delta = 0.f;

		while (ifs >> name >> delta)
		{
			this->Background[name]->setPosition(sf::Vector2f(this->view.getCenter().x - this->window->getSize().x / 2, 0.0f));
			this->Background[name]->setTextureRect(sf::IntRect(this->view.getCenter().x * delta, 0, 1920, 1080));
		}
	}

	ifs.close();

	this->startBox.setPosition(sf::Vector2f(this->view.getCenter().x - this->window->getSize().x / 2.f, 0));
	this->loadingBackground.setPosition(sf::Vector2f(this->view.getCenter().x, 0));
	//this->loading.setPosition(sf::Vector2f(this->view.getCenter().x, this->window->getSize().y / 7 * 6));
	this->loading.setPosition(sf::Vector2f(this->loadingBackground.getPosition().x + this->loadingBackground.getSize().x / 2, this->window->getSize().y / 7 * 6));
}

//Update button
void GameStates::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonsPressed("MAIN MENU"))
	{
		this->player->die = true;
		this->music.pause();
		this->unpauseState();
		this->initGameWin("MISSION FAIL!!", false);
		this->win = true;
	}
	if (this->pmenu->isButtonsPressed("HIGH SCORE"))
	{
		this->highscoreState();
	}
	if (this->pmenu->isButtonsPressed("CONTINUE"))
	{
		this->music.play();
		this->unpauseState();
	}
}

void GameStates::updateBackButton()
{
	if (this->scoreBack->isButtonsPressed("BACK"))
	{
		this->scoreBack->initVeriables();
		this->unhighscoreState();
	}
}

void GameStates::updateKeepItems(Platform& platform, const float& deltaTime)
{
	for (int i = 0; i < this->items.size(); ++i)
	{
		this->totalKeepItemsTime += itemClock.restart().asSeconds();

		if (platform.GetCollider().CheckCollisionPlatform(this->items[i]->GetCollider(), this->direction, 1.0f))
			this->items[i]->onCollision(this->direction);

		this->items[i]->update(deltaTime);

		if (this->player->updateAction() == 4)
		{
			if (this->items[i]->GetCollider().CheckCollision(this->player->GetCollider(), this->direction, this->hit, 1.0f))
			{
				if (this->totalKeepItemsTime > 0.5f)
				{
					this->updatePickup(*items[i]);
					this->items.erase(this->items.begin() + i--);
					i = this->items.size();

					this->totalKeepItemsTime = 0.f;
				}
			}
		}
		else if (!this->items[i]->getStatus())
		{
			this->items.erase(this->items.begin() + i--);
		}
	}

}

void GameStates::updatePickup(Item& item)
{
	int num = item.getItem();
	if (num < 2)
	{
		this->countItems[num]++;
	}
	else if (num == 2)
	{
		this->HP += 300;
	}
	else if (num == 3)
	{
		this->MANA += 10;
	}
	else if (num == 4)
	{
		this->totaltimepowerup.push_back(0.f);
		this->power = this->power + 3 ;
		this->clockpower.restart().asSeconds();
	}
}

//Update Score
void GameStates::UpdateAttack(sf::Event sfEvent)
{
	this->hit = 0;
	if (!this->golem.empty())
	{
		for (int i = 0; i < this->golem.size(); ++i)
		{
			this->hit = 0;
			//Player attack
			if (this->sword->GetCollider().CheckCollision(this->golem[i]->GetCollider(), this->direction, this->hit, 1.0f))
			{
				if (this->player->getAttack())
				{
					switch (this->player->updateAction())
					{
					case 6:
						this->hit *= 0.1f * this->power; break;

					case 7:
						this->hit *= 0.3f * this->power; break;

					case 8:
						this->hit *= 0.5f * this->power;  break;

					default:
						this->hit = 0;   break;
					}
				}
				else
					this->hit = 0;

				this->hit = abs(this->hit);
				this->golem[i]->updateHp(this->hit);

			}
			if (this->golem[i]->updateHp(0) == 0)
				this->hit = -1;

			this->golem[i]->Update(this->deltaTime, this->player->getPosition(), this->hit,this->player->die);

			//Enemies attack
			this->hit = 0;

			if (this->player->GetCollider().CheckCollisionSwordEnemy(this->golem[i]->GetColliderSword(), this->direction, this->hit, 1.0f))
			{
				if (this->golem[i]->updateAttack() == 3)
				{
					if (this->golem[i]->getAttack())
					{
						this->player->updateHurt(static_cast<sf::Vector2f>(this->golem[i]->getPosition()));
						this->HP -= (abs(this->hit) + 40) * this->states;
						//this->golem[i]->Update(this->deltaTime, this->player->getPosition(), 10);
					}
				}
			}
			//Enemies die
			if (this->golem[i]->checkDie())
			{
				int random = rand() % (this->itemsCount + 2);
				if (random < this->itemsCount)
					this->items.push_back(new Item(&this->itemTexture[random], random, sf::Vector2f(100, 100), sf::Vector2f(this->golem[i]->getPosition().x, this->golem[i]->getPosition().y)));
				this->score += this->golem[i]->updateScore();
				this->golem.erase(this->golem.begin() + i);
			}
		}
	}

	if (!this->boss.empty())
	{
		for (int i = 0; i < this->boss.size(); ++i)
		{
			this->hit = 0;
			//Player attack
			if (this->sword->GetCollider().CheckCollision(this->boss[i]->GetCollider(), this->direction, this->hit, 1.0f))
			{
				if (this->player->getAttack())
				{
					switch (this->player->updateAction())
					{
					case 6:
						this->hit *= 0.1f * this->power * 2; break;

					case 7:
						this->hit *= 0.3f * this->power * 2; break;

					case 8:
						this->hit *= 0.5f * this->power * 2;  break;

					default:
						this->hit = 0;   break;
					}
				}
				else
					this->hit = 0;

				this->hit = abs(this->hit);
				this->boss[i]->updateHp(this->hit);

			}
			if (this->boss[i]->updateHp(0) == 0)
				this->hit = -1;

			this->boss[i]->Update(this->deltaTime, this->player->getPosition(), this->hit, this->player->die);

			//Enemies attack
			this->hit = 0;

			if (this->player->GetCollider().CheckCollisionSwordEnemy(this->boss[i]->GetColliderSword(), this->direction, this->hit, 1.0f))
			{
				if (this->boss[i]->updateAttack() == 3)
				{
					if (this->boss[i]->getAttack())
					{
						this->player->updateHurt(static_cast<sf::Vector2f>(this->boss[i]->getPosition()));
						this->HP -= (abs(this->hit) + 45) * this->states;
						//this->boss[i]->Update(this->deltaTime, this->player->getPosition(), 10, this->player->die);
					}
				}
			}
			//Enemies die
			if (this->boss[i]->checkDie())
			{
				//this->HP += 250 * this->states;
				this->countItems[0] += 5;
				this->countItems[1] += 5;
				this->score += this->boss[i]->updateScore();
				this->boss.erase(this->boss.begin() + i--);
			}
		}
	}
	else
	{
		this->seeBoss = false;
		if (!this->win)
		{
			if (this->states == 3)
			{
				this->score += this->HP;
				this->initGameWin("MISSION COMPLETE", true);
				this->win = true;
			}
			else
			{
				if (this->player->getPosition().x > 13500 and this->items.empty())
				{
					this->start = false;
					this->endThisState = true;
					this->change = false;
				}
				if (this->fadeStart == 255)
				{
					this->states++;
					this->initBackground();

					while (!this->platforms.empty())
						this->platforms.erase(this->platforms.begin());

					this->initPlatform();
					this->initMonster();

					this->player->setPosition(sf::Vector2f(1000, this->player->getPosition().y));
					this->view.setCenter(sf::Vector2f(1000, this->window->getSize().y / 2.0f));
					this->endThisState = false;

					if (!this->totaltimepowerup.empty())
					{
						this->power = this->power - 3;
						this->totaltimepowerup.erase(this->totaltimepowerup.begin());
					}

					this->power = this->power + 3;
				}
			}
		}
	}


	if (this->HP <= 0)
	{
		this->HP = 0;
		this->player->die = true;
		this->initGameWin("MISSION FAIL!!", true);
		this->win = true;
	}
}

void GameStates::throwItem()
{
	this->totaltimeuseitem += this->clockItem.restart().asSeconds();
	if (this->totaltimeuseitem > 0.3)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) and this->countItems[0] > 0)
		{
			this->throwItems.push_back(new ThrowingState(&this->itemTextureMain, this->player->getPosition(), sf::Vector2u(8, 4), 0, 5, 0.01f, 1200.f * this->player->getScale().x / 2, 150));
			this->countItems[0]--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) and this->countItems[1] > 0)
		{
			this->throwItems.push_back(new ThrowingState(&this->itemTextureMain, this->player->getPosition(), sf::Vector2u(8, 4), 1, 8, 0.01f, 1200.f * this->player->getScale().x / 2, 120));
			this->countItems[1]--;
		}

		this->totaltimeuseitem = 0.f;
	}

	for (int i = 0; i < this->throwItems.size(); ++i)
	{
		this->hit = 0.f;
		this->throwItems[i]->update(this->deltaTime);
		for (int golem = 0; golem < this->golem.size(); golem++)
			if (this->golem[golem]->GetCollider().CheckCollisionThrowing(this->throwItems[i]->GetCollider(), this->direction))
			{
				//this->throwItems[i]->onCollision(this->direction);
				this->golem[golem]->updateHp(this->throwItems[i]->getPower());
				this->golem[golem]->Update(this->deltaTime, this->player->getPosition(), this->throwItems[i]->getPower(), this->player->die);
				golem = this->golem.size();
				this->throwItems.erase(this->throwItems.begin() + i);
				--i;
			}
	}

	for (int i = 0; i < this->throwItems.size(); ++i)
	{
		if (!this->boss.empty())
		{
			for (int k = 0; k < boss.size(); ++k)
				if (this->boss[k]->GetCollider().CheckCollisionThrowing(this->throwItems[i]->GetCollider(), this->direction))
				{
					//this->throwItems[i]->onCollision(this->direction);
					this->boss[k]->updateHp(this->throwItems[i]->getPower());
					this->boss[k]->Update(this->deltaTime, this->player->getPosition(), this->throwItems[i]->getPower(), this->player->die);
					k = this->boss.size();
					this->throwItems.erase(this->throwItems.begin() + i);
					--i;
				}
		}
	}

	for (int i = 0; i < this->throwItems.size(); ++i)
	{
		if (abs(this->throwItems[i]->getVeclocity()) < 20.f)
		{
			this->throwItems.erase(this->throwItems.begin() + i);
			--i;
		}
	}
}

void GameStates::updateBoss()
{
	if(!this->boss.empty())
		if (this->boss[0]->getPosition().x < this->window->getPosition().x + this->window->getSize().x / 2 + 100)
		{
			this->seeBoss = true;
		}
}

//Update endgame
void GameStates::updateGamewin()
{
	if (this->gamewin->isButtonsPressed("MAIN MENU"))
	{
		this->music.pause();
		this->endStates();
	}

	this->totalTimeStart += this->clockstart.restart().asSeconds();
	if (this->totalTimeStart > 0.05)
	{
		this->fade += 5;
		this->totalTimeStart = 0;
	}
	if (this->fade > 180)
		this->fade = 180;

	this->fadeBox.setFillColor(sf::Color(10, 10, 10, this->fade));

}

//Game Update
void GameStates::update(const float& deltaTime, sf::Event sfEvent)
{
	this->updateMousePositions();
	this->updateButtonInput();

	if (this->win)
	{
		if (fade == 180)
			this->gamewin->updateScore();
		this->gamewin->update(this->mousePosView);
		this->gamewin->updatePosition(this->fadeBox.getPosition(), this->fadeBox.getSize());
		this->updateGamewin();
	}
	
	if (this->highScore)
	{
		this->scoreBack->updatePosition(this->Background["Sky"]->getPosition().x, this->Background["Sky"]->getPosition().y, static_cast<sf::Vector2f>(this->window->getSize()));
		this->scoreBack->update(this->mousePosView);
		this->updateBackButton();
	}
	else if (!this->pause and !this->howtoplay)
	{
		this->updateDelta();

		//Update input
		this->updateInput(deltaTime);
		if(!this->win)
			this->updatePauseInput(deltaTime);

		//Update background
		this->updateBackground(deltaTime);

		//Update platform
		for (Platform& platform : platforms) 
		{
			if (platform.GetCollider().CheckCollisionPlatform(this->player->GetCollider(), this->direction, 1.0f))
				this->player->onCollision(this->direction);

			
				for (Monster* i : this->golem)
				{
					if (platform.GetCollider().CheckCollisionPlatform(i->GetCollider(), this->direction, 1.0f))
						i->onCollision(this->direction);
				}

				for(Boss* boss : this->boss)
				{
					if (platform.GetCollider().CheckCollisionPlatform(boss->GetCollider(), this->direction, 1.0f))
						boss->onCollision(this->direction);
				}

			if (!this->items.empty())
			{
				this->updateKeepItems(platform, deltaTime);
			}
		}

		//Update countdown
		this->updateCountdown_skill(this->player->getCountdown_stSkill(), this->player->getCountdown_ndSkill(), this->player->getCountdown_rdSkill());

		//Update player
		this->player->Update(this->deltaTime, this->win, this->view.getCenter().x - (this->window->getSize().x / 2) + 200, this->MANA);
		this->sword->setPosition(this->player->getPosition());
		this->throwItem();

		//Update monster
		this->UpdateAttack(sfEvent);

		//Update window game
		this->updatePositionWindowGame();

		//Update view
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or this->player->getPosition().x < this->view.getCenter().x or this->seeBoss)
			this->view.setCenter(this->view.getCenter());
		else if(this->player->getPosition().x >= 1000 and this->player->getPosition().x < 13000)
			this->view.setCenter(sf::Vector2f(this->player->getPosition().x, this->window->getSize().y / 2.0f));
	}
	else
	{
		this->pmenu->updatePosition(this->Background["Sky"]->getPosition().x, this->Background["Sky"]->getPosition().y, this->window->getSize().x / 2.0f);
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

	this->startBox.setPosition(sf::Vector2f(this->view.getCenter().x, 0));
	this->updateBoss();
}

//Render

void GameStates::renderBackground(sf::RenderTarget& target)
{
	std::ifstream ifs("config/background.ini");

	if (ifs.is_open())
	{
		std::string name = "";
		float delta = 0.f;

		while (ifs >> name >> delta)
		{
			this->Background[name]->render(target);
		}

	}

	ifs.close();
}

void GameStates::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->renderBackground(*target);

	//Platforms
	for (Platform& platform : this->platforms)
		platform.Draw(target);
	
	//Items
	for (Item* item : this->items)
		item->render(*target);

	//Monsters
	for (Monster* i : this->golem)
	{
		if (i->updateAttack() != 3)
			i->Draw(*target);
	}
	
	//Player
	this->player->Draw(target);

	//Monsters
	for (Monster* i : this->golem)
	{
		if (i->updateAttack() == 3)
			i->Draw(*target);
	}

	for (Boss* boss : this->boss)
		boss->Draw(*target);

	//Player
	if (this->player->updateAction() == 6 or this->player->updateAction() == 7 or this->player->updateAction() == 8 )
		this->player->Draw(target);

	//Throw item
	for (ThrowingState* item : this->throwItems)
		item->render(target);

	//GUI
	if(!this->win)
		this->renderWindowGameState(target);

	//Pause
	if (this->win)
	{
		target->draw(this->fadeBox);

		if (this->fade == 180)
		{
			this->gamewin->render(*target);
		}
	}
	else if (this->highScore)
	{
		this->scoreBack->render(*target);
	}
	else if (this->pause) 
		this->pmenu->render(*target);

	if (!this->start)
	{
		this->totalTimeStart += this->clockstart.restart().asSeconds();
		if (this->totalTimeStart > 0.05)
		{
			if(this->endThisState)
				this->fadeStart += 15;
			else
				this->fadeStart -= 15;
			this->startBox.setFillColor(sf::Color(0, 0, 0, this->fadeStart));
			this->totalTimeStart = 0;
		}

		target->draw(this->startBox);
		if (this->fadeStart == 0)
		{
			this->start = true;
		}
	}

	/*if (!this->change and this->states != 3 and this->fadeStart == 255)
	{
		this->totalTimeStart += this->clockstart.restart().asSeconds();
		if (this->totalTimeStart > 0.3)
		{
			this->state = !this->state;
			this->totalTimeStart = 0;
		}

		target->draw(this->loadingBackground);
		if (this->state)
		{
			target->draw(this->loading);
		}
	}*/
}

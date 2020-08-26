#include "WindowGameState.h"

void WindowGameState::initTextures()
{
	std::ifstream readtext("config/gamewindowtexture.ini");

	if (readtext.is_open())
	{
		std::string file = "";
		std::string name = "";

		while (readtext >> file >> name)
		{
			this->texture[name].loadFromFile(file + "/" + name + ".png");
			this->texture[name].setSmooth(true);
		}
	}

	readtext.close();
}

void WindowGameState::initButtons()
{
	float width = 96 ;
	float height = 90 ;
	float x = (this->window->getSize().x ) - 120;
	float y = 110;

	this->buttons["PAUSE"] = new gui::Button(&this->texture["pause"], x, y * 0 + 20, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	this->buttonname.push_back("PAUSE");

	/*this->buttons["OPTION"] = new gui::Button(&this->texture["set"], x, y * 1 + 20, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	this->buttonname.push_back("OPTION");*/

	this->buttons["HOW"] = new gui::Button(&this->texture["how"], x, y * 1 + 20, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
		
	this->buttonname.push_back("HOW");

	this->howbutton = new gui::Button(&this->texture["incorrect"], x, y, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

}

void WindowGameState::initLockSkill()
{
	float width = 70 ;
	float height = 70 ;
	float x = 100.f;
	float y = this->window->getSize().y / 9 * 2;

	for (int row = 1; row < 4; ++row)
	{
		this->buttons["SKILL" + std::to_string(row)] = new gui::Button(&this->texture["SKILL" + std::to_string(row)], x * row + 250, y, width, height, 30,
			nullptr, "",
			sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
	}
}

void WindowGameState::initBagButton()
{
	float width = 60;
	float height = 60;
	float x = 20.f;
	float y = this->window->getSize().y / 11 * 10;

	/*this->buttons["BAG_BUTTON"] = new gui::Button(&this->texture["bagbutton"], x, y, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255)
	);*/

	width = 64 ;
	height = 64 ;
	x = 130;

	this->buttons["SHURIKEN"] = new gui::Button(&this->texture["SHURIKEN_BUTTON"], x, y, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	x = 200;

	this->buttons["KUNAI"] = new gui::Button(&this->texture["KUNAI_BUTTON"], x, y, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
	
	for (int i = 0; i < 2; ++i)
	{
		this->countItemsText[i].setFont(font);
		this->countItemsText[i].setFillColor(sf::Color::Black);
		this->countItemsText[i].setCharacterSize(20);
		this->countItemsText[i].setOutlineThickness(1);
		this->countItemsText[i].setOutlineColor(sf::Color::White);
	}


}

void WindowGameState::initHPBar()
{
	sf::Vector2f size(305, 74);
	this->hpbarshape.setTexture(&this->texture["hpbar"]);
	this->hpbarshape.setSize(size * 2.f);

	//Profile
	this->profile.setRadius(60);
	this->profile.setFillColor(sf::Color::White);
	this->profile.setOutlineThickness(5);
	this->profile.setOutlineColor(sf::Color::Black);
	this->profile.setOrigin({ this->profile.getGlobalBounds().width / 2.f, this->profile.getGlobalBounds().height / 2.f });

	this->playerProfile.setRadius(60);
	this->playerProfile.setTexture(&this->texture["PNG_PLAYER_1"]);
	this->playerProfile.setOrigin({ this->profile.getGlobalBounds().width / 2.f, this->profile.getGlobalBounds().height / 2.f });

	//HP
	this->heart.setTexture(&this->texture["HEART"]);
	this->heart.setTextureRect(sf::IntRect(20, 20, 40, 40));
	this->heart.setSize(sf::Vector2f(60, 60));
	this->heart.setOrigin(this->heart.getSize() / 2.f);

	this->hpStatus.setSize(sf::Vector2f(480, 40));
	this->hpStatus.setOrigin(sf::Vector2f(0, 20));
	this->hpStatus.setFillColor(sf::Color(0, 200, 15));

	this->hpBG.setSize(sf::Vector2f(480, 40));
	this->hpBG.setOrigin(sf::Vector2f(0, 20));
	this->hpBG.setFillColor(sf::Color(sf::Color::White));
	this->hpBG.setOutlineThickness(3);
	this->hpBG.setOutlineColor(sf::Color::White);

	this->hpEnd.setRadius(20);
	this->hpEnd.setFillColor(sf::Color(0, 200, 15));
	this->hpEnd.setOrigin({ this->hpEnd.getGlobalBounds().width / 2.f, this->hpEnd.getGlobalBounds().height / 2.f });

	this->hpEndBG.setRadius(20);
	this->hpEndBG.setFillColor(sf::Color::White);
	this->hpEndBG.setOrigin({ this->hpEnd.getGlobalBounds().width / 2.f, this->hpEnd.getGlobalBounds().height / 2.f });
	this->hpEndBG.setOutlineThickness(3);
	this->hpEndBG.setOutlineColor(sf::Color::White);

	//Mana
	this->mana.setTexture(&this->texture["MANA"]);
	//this->mana.setTextureRect(sf::IntRect(10, 10, 60, 60));
	this->mana.setSize(sf::Vector2f(60, 60));
	this->mana.setOrigin(this->heart.getSize() / 2.f);

	this->manaStatus.setSize(sf::Vector2f(190, 20));
	this->manaStatus.setOrigin(sf::Vector2f(0, 10));
	this->manaStatus.setFillColor(sf::Color(100, 197, 215));

	this->manaBG.setSize(sf::Vector2f(190, 20));
	this->manaBG.setOrigin(sf::Vector2f(0, 10));
	this->manaBG.setFillColor(sf::Color::White);
	this->manaBG.setOutlineThickness(3);
	this->manaBG.setOutlineColor(sf::Color::White);

	this->manaEnd.setRadius(10);
	this->manaEnd.setFillColor(sf::Color(100, 197, 215));
	this->manaEnd.setOrigin({ this->manaEnd.getGlobalBounds().width / 2.f, this->manaEnd.getGlobalBounds().height / 2.f });

	this->manaEndBG.setRadius(10);
	this->manaEndBG.setFillColor(sf::Color::White);
	this->manaEndBG.setOrigin({ this->manaEnd.getGlobalBounds().width / 2.f, this->manaEnd.getGlobalBounds().height / 2.f });
	this->manaEndBG.setOutlineThickness(3);
	this->manaEndBG.setOutlineColor(sf::Color::White);
}

void WindowGameState::initScoreBar()
{
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(15);
	this->scoreText.setOutlineColor(sf::Color::White);
	this->scoreText.setOutlineThickness(3);
	this->scoreText.setFillColor(sf::Color::Blue);
	this->scoreText.setLetterSpacing(2);

	this->HPbar.setFont(this->font);
	this->HPbar.setString(std::to_string(this->HP));
	this->HPbar.setCharacterSize(15);
	this->HPbar.setOutlineColor(sf::Color::White);
	this->HPbar.setOutlineThickness(3);
	this->HPbar.setFillColor(sf::Color::Black);
	this->HPbar.setLetterSpacing(2);

	this->ManaBar.setFont(this->font);
	this->ManaBar.setString(std::to_string(this->MANA));
	this->ManaBar.setCharacterSize(15);
	this->ManaBar.setOutlineColor(sf::Color::White);
	this->ManaBar.setOutlineThickness(1);
	this->ManaBar.setFillColor(sf::Color::Black);
	this->ManaBar.setLetterSpacing(1);

	this->powerText.setFont(this->font);
	this->powerText.setCharacterSize(20);
	this->powerText.setOutlineColor(sf::Color::Yellow);
	this->powerText.setOutlineThickness(1);
	this->powerText.setFillColor(sf::Color::Black);
	this->powerText.setLetterSpacing(1);
	this->powerText.setString("POWER X");

	this->fistRec.setTexture(&this->texture["FIST"]);
	this->fistRec.setSize(sf::Vector2f(35, 29));
	this->fistRec.setOrigin(this->fistRec.getSize() / 2.f);

	this->nameBox.setSize(sf::Vector2f(300, 50));
	this->nameBox.setFillColor(sf::Color(250, 200, 200, 255));
	this->nameBox.setOutlineColor(sf::Color(50, 25, 2, 255));
	this->nameBox.setOutlineThickness(10);

	this->howTexture.loadFromFile("items/HOWTOPLAY.png");
	this->how.setTexture(&this->howTexture);
	this->how.setSize({ 1100,600 });
	this->how.setOrigin({ 550,300 });
}

void WindowGameState::initCountdown_skill()
{
	for (int skill = 0; skill < 3; skill++)
	{
		this->countdown_skill[skill].setFont(this->font);
		this->countdown_skill[skill].setCharacterSize(25);
		this->countdown_skill[skill].setFillColor(sf::Color::Black);
		this->countdown_skill[skill].setOutlineThickness(2);
		this->countdown_skill[skill].setOutlineColor(sf::Color::White);

		this->colldownskill[skill].setSize({ 70,70 });
		this->colldownskill[skill].setOrigin({ 35,35 });
		this->colldownskill[skill].setFillColor(sf::Color(150, 150, 150, 150));
		this->colldownskill[skill].setPosition(this->buttons["SKILL" + std::to_string(skill+1)]->getPosition());
	}
}

WindowGameState::WindowGameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::Font& font) :
	State(window, supportedKeys, states), font(font)
{
	this->initTextures();
	this->initButtons();
	this->initLockSkill();
	this->initBagButton();
	this->initHPBar();
	this->initCountdown_skill();
	this->initScoreBar();

	this->countItems[0] = this->countItems[1] = 10;
}

WindowGameState::~WindowGameState()
{
}

void WindowGameState::updateBagItems()
{
	for (int i = 0; i < 2; ++i)
	{
		this->countItemsText[i].setString(std::to_string(this->countItems[i]));
		this->countItemsText[i].setOrigin(sf::Vector2f(this->countItemsText[i].getGlobalBounds().width / 2.f, this->countItemsText[i].getGlobalBounds().height / 2.f));
	}

	this->countItemsText[0].setPosition(
		sf::Vector2f(
			this->buttons["SHURIKEN"]->getPosition().x + (this->buttons["SHURIKEN"]->getSize().x / 2),
			this->buttons["SHURIKEN"]->getPosition().y
		)
	);

	this->countItemsText[1].setPosition(
		sf::Vector2f(
			this->buttons["KUNAI"]->getPosition().x + (this->buttons["KUNAI"]->getSize().x / 2),
			this->buttons["KUNAI"]->getPosition().y
		)
	);
}

void WindowGameState::updateMana()
{
	this->manaTime += this->manaClock.restart().asSeconds();
	if (this->manaTime > 2)
	{
		this->MANA += 5.f;
		this->manaTime = 0;
	}

	if (this->MANA > 100)
		this->MANA = 100;
	int size = 190 * this->MANA / 100;
	this->manaStatus.setSize(sf::Vector2f(size, this->manaStatus.getSize().y));
}

void WindowGameState::updateHP()
{
	if (this->HP > 10000)
		this->HP = 10000;
	int size = 480 * this->HP / 10000;
	this->hpStatus.setSize(sf::Vector2f(size, 40));
}

void WindowGameState::updatePowerUp()
{
	if (!this->totaltimepowerup.empty())
	{
		float time = this->clockpower.restart().asSeconds();
		for (int i = 0; i < this->totaltimepowerup.size(); ++i)
		{
			this->totaltimepowerup[i] += time;
			if (this->totaltimepowerup[i] > 10.f)
			{
				this->power -= 3;
				this->totaltimepowerup.erase(this->totaltimepowerup.begin() + i);
				i--;
			}
		}
	}

	this->powerText.setString("POWER X");
	this->powerText.setOrigin(sf::Vector2f(this->powerText.getGlobalBounds().width / 2, this->powerText.getGlobalBounds().height / 2));
	this->powerText.setString("POWER X" + std::to_string(this->power));
	this->powerText.setPosition(sf::Vector2f(this->manaEndBG.getPosition().x + 150, this->manaEndBG.getPosition().y -5 ));
}

void WindowGameState::updateScorBar()
{
	this->nameBox.setPosition(sf::Vector2f(this->profile.getPosition().x, this->profile.getPosition().y + this->profile.getRadius() + 30));
	this->scoreText.setString(this->namePlayer + " : " + std::to_string(this->score));
	this->scoreText.setOrigin(sf::Vector2f(this->scoreText.getGlobalBounds().width / 2, this->scoreText.getGlobalBounds().height / 2.f));
	this->scoreText.setPosition(
		sf::Vector2f(
			this->profile.getPosition().x + this->nameBox.getGlobalBounds().width / 2.f, 
			this->profile.getPosition().y + this->profile.getRadius() + 30 + this->nameBox.getGlobalBounds().height / 2.f - this->scoreText.getGlobalBounds().height / 2.f
		)
	);
}

void WindowGameState::updateHPbar()
{
	if (this->HP < 500)
	{
		this->hpStatus.setFillColor(sf::Color::Red);
		this->hpEnd.setFillColor(sf::Color::Red);
		//this->HPbar.setFillColor(sf::Color::Red);
	}
	else if (this->HP < 1500)
	{
		this->hpStatus.setFillColor(sf::Color::Yellow);
		this->hpEnd.setFillColor(sf::Color::Yellow);
		//this->HPbar.setFillColor(sf::Color::Yellow);
	}
	else
	{
		this->hpStatus.setFillColor(sf::Color(0, 200, 15));
		this->hpEnd.setFillColor(sf::Color(0, 200, 15));
	}

	this->HPbar.setString(std::to_string(this->HP) + " / 10000");
	this->HPbar.setOrigin(sf::Vector2f(this->HPbar.getGlobalBounds().width / 2.f, this->HPbar.getGlobalBounds().height / 2.f));
	this->HPbar.setPosition(sf::Vector2f(this->hpBG.getPosition().x + this->hpBG.getSize().x / 2.f, this->hpBG.getPosition().y));

	this->ManaBar.setString(std::to_string(this->MANA) + " / 100");
	this->ManaBar.setOrigin(sf::Vector2f(this->ManaBar.getGlobalBounds().width / 2.f, this->ManaBar.getGlobalBounds().height / 2.f));
	this->ManaBar.setPosition(sf::Vector2f(this->manaBG.getPosition().x + this->manaBG.getSize().x / 2.f, this->manaBG.getPosition().y));
}

void WindowGameState::updateCountdown_skill(int st, int nd, int rd)
{
	int countdown[] = { st, nd, rd };

	for (int skill = 0; skill < 3; ++skill)
	{
		this->countdown_skill[skill].setString(std::to_string(countdown[skill]));
		this->countdown_skill[skill].setOrigin(sf::Vector2f(this->countdown_skill[skill].getGlobalBounds().width / 2, this->countdown_skill[skill].getGlobalBounds().height / 2));
		this->countdown_skill[skill].setPosition(
			sf::Vector2f(
				this->buttons["SKILL" + std::to_string(skill + 1)]->getPosition().x + this->buttons["SKILL" + std::to_string(skill + 1)]->getSize().x / 2,
				this->buttons["SKILL" + std::to_string(skill + 1)]->getPosition().y + this->buttons["SKILL" + std::to_string(skill + 1)]->getSize().y / 2
			)
		);

		this->colldownskill[skill].setPosition(
			sf::Vector2f(
				this->buttons["SKILL" + std::to_string(skill + 1)]->getPosition().x + this->buttons["SKILL" + std::to_string(skill + 1)]->getSize().x / 2,
				this->buttons["SKILL" + std::to_string(skill + 1)]->getPosition().y + this->buttons["SKILL" + std::to_string(skill + 1)]->getSize().y / 2
			)
		);
	}
}

void WindowGameState::updateButtonInput()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if(this->buttons["PAUSE"]->isPressed() and !this->howtoplay)
		this->pauseState();

	if (this->buttons["HOW"]->isPressed())
		this->howtoplayState();

	this->howbutton->update(this->mousePosView);
	if (this->howbutton->isPressed())
	{
		this->unhowtoplayState();
		this->start = false;
	}

}

void WindowGameState::updatePositionWindowGame()
{
	float x = 100.f;
	float y = this->window->getSize().y / 9 * 2;

	for (auto& button : this->buttonname)
	{
		this->buttons[button]->setPosition(sf::Vector2f(this->view.getCenter().x + this->view.getSize().x / 2.f - 120, this->buttons[button]->getPosition().y));
	}
	for (int skill = 1; skill < 4; ++skill)
	{
		this->buttons["SKILL" + std::to_string(skill)]->setPosition(
			sf::Vector2f(
				this->view.getCenter().x - this->view.getSize().x / 2.f + x * skill + 310,
				this->buttons["SKILL" + std::to_string(skill)]->getPosition().y
			)
		);
	}

	this->buttons["SHURIKEN"]->setPosition(
		sf::Vector2f(
			this->view.getCenter().x - this->view.getSize().x / 2.f + 60,
			this->buttons["SHURIKEN"]->getPosition().y
		)
	);

	this->buttons["KUNAI"]->setPosition(
		sf::Vector2f(
			this->view.getCenter().x - this->view.getSize().x / 2.f + 150,
			this->buttons["KUNAI"]->getPosition().y
		)
	);

	this->updateHP();
	this->updateMana();
	this->updateBagItems();
	this->updateScorBar();
	this->updateHPbar();
	this->updatePowerUp();

	//HP bar
	this->hpbarshape.setPosition(sf::Vector2f(this->view.getCenter().x - this->view.getSize().x / 2.f + 85,	20));
	this->profile.setPosition(sf::Vector2f(this->hpbarshape.getPosition().x, 94));
	this->playerProfile.setPosition(this->profile.getPosition());
	this->heart.setPosition(sf::Vector2f(this->hpbarshape.getPosition().x + 90, this->hpbarshape.getPosition().y + this->hpbarshape.getSize().y / 3.f));
	this->mana.setPosition(sf::Vector2f(this->hpbarshape.getPosition().x + 90, this->hpbarshape.getPosition().y + this->hpbarshape.getSize().y / 4.f * 3.f));

	this->hpStatus.setPosition(this->heart.getPosition());
	this->hpBG.setPosition(this->heart.getPosition());
	this->manaStatus.setPosition(this->mana.getPosition());
	this->manaBG.setPosition(this->mana.getPosition());

	this->hpEnd.setPosition(this->hpStatus.getPosition().x + this->hpStatus.getGlobalBounds().width, this->hpStatus.getPosition().y);
	this->hpEndBG.setPosition(this->hpBG.getPosition().x + this->hpBG.getGlobalBounds().width, this->hpBG.getPosition().y);

	this->manaEnd.setPosition(this->manaStatus.getPosition().x + this->manaStatus.getGlobalBounds().width, this->manaStatus.getPosition().y);
	this->manaEndBG.setPosition(this->manaBG.getPosition().x + this->manaBG.getGlobalBounds().width, this->manaBG.getPosition().y);

	this->fistRec.setPosition(sf::Vector2f(this->manaEndBG.getPosition().x + 60, this->mana.getPosition().y));

	this->how.setPosition(sf::Vector2f( this->view.getCenter().x, this->window->getSize().y / 2 ));

	this->howbutton->setPosition(sf::Vector2f(
		this->how.getPosition().x + this->how.getSize().x / 2 - this->howbutton->getSize().x - 40,
		this->how.getPosition().y - this->how.getSize().y / 2 + 30
		)
	);
}

void WindowGameState::renderWindowGameState(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	if (!this->howtoplay and !this->start)
	{
		for (auto& button : this->buttons)
			button.second->render(*target);

		for (int i = 0; i < 3; ++i)
		{
			if (this->countdown_skill[i].getString() != "0")
			{
				target->draw(this->colldownskill[i]);
				target->draw(this->countdown_skill[i]);
			}
		}

		target->draw(this->hpbarshape);
		target->draw(this->profile);
		target->draw(this->playerProfile);
		target->draw(this->hpBG);
		target->draw(this->hpEndBG);
		target->draw(this->hpStatus);
		target->draw(this->hpEnd);
		target->draw(this->hpEnd);
		target->draw(this->manaBG);
		target->draw(this->manaEndBG);
		target->draw(this->manaStatus);
		target->draw(this->manaEnd);
		target->draw(this->heart);
		target->draw(this->mana);
		target->draw(this->fistRec);

		//this->sword->Draw(target);
		target->draw(this->nameBox);
		target->draw(this->scoreText);
		target->draw(this->HPbar);
		target->draw(this->ManaBar);
		target->draw(this->powerText);


		for (int i = 0; i < 2; ++i)
		{
			target->draw(this->countItemsText[i]);
		}
	}

	if (this->howtoplay or this->start)
	{
		target->draw(this->how);
		this->howbutton->render(*target);
	}
}

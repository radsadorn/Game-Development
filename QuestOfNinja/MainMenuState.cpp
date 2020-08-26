#include "MainMenuState.h"

//initializer function
void MainMenuState::initVariable()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().y * 1279 / 716),
			static_cast<float>(this->window->getSize().y)
		)
	);

	//this->backgroundTexture.loadFromFile("map/menuBG.jpg");
	this->backgroundTexture.loadFromFile("background/MAINMENU.jpg");
	this->backgroundTexture.setSmooth(true);
	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("font/EDmuzazhi.ttf"))
		throw("ERROE::MAINMENUSTATE::COUND NOT LOAD FONT");

	if (!this->mefont.loadFromFile("font/njnaruto.ttf"))
		throw("ERROE::MAINMENUSTATE::COUND NOT LOAD FONT");
}

void MainMenuState::initHighScore()
{
	this->scoreBack = new ScoreState(*this->window, this->font);

	this->scoreBack->addButton("BACK", this->window->getSize().y / 6.f, 5, "BACK");
}

void MainMenuState::initName()
{
	/*this->name.setString("Quest of Ninja");
	this->name.setFont(this->font);
	this->name.setCharacterSize(150);
	this->name.setFillColor(sf::Color::Black);
	this->name.setOutlineColor(sf::Color::White);
	this->name.setLetterSpacing(2);
	this->name.setOutlineThickness(5);
	this->name.setPosition(sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f));
	this->name.setOrigin(sf::Vector2f(this->name.getGlobalBounds().width / 2.f, this->name.getGlobalBounds().height / 2.f));*/
	this->LOGO.loadFromFile("sprite/LOGO.png");
	this->LOGO.setSmooth(true);
	this->logo.setTexture(&this->LOGO);
	this->logo.setSize(sf::Vector2f(1000, 250));
	this->logo.setOrigin(this->logo.getSize() / 2.f);
	this->logo.setPosition(sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f - 10));

	this->me.setString("62010966\tSutthirat phutho\tCOMPUTER ENGINEERING\tKMITL");
	this->me.setFont(this->mefont);
	this->me.setCharacterSize(20);
	this->me.setLetterSpacing(2);
	this->me.setFillColor(sf::Color::Black);
	this->me.setOutlineColor(sf::Color::White);
	this->me.setOutlineThickness(1);
	this->me.setOrigin(sf::Vector2f(this->me.getGlobalBounds().width / 2, 0));
	this->me.setPosition(
		sf::Vector2f(
			this->view.getCenter().x + this->window->getSize().x / 2,
			this->window->getSize().y - this->me.getGlobalBounds().height -10
		)
	);
	//this->me.setOrigin(sf::Vector2f(this->name.getGlobalBounds().width / 2.f, this->name.getGlobalBounds().height / 2.f));
}

void MainMenuState::initHowtoPlay()
{
	this->howBack = new HowState(*this->window, this->font);

	this->howBack->addButton("BACK", this->window->getSize().y / 6.f, 5, "BACK");
}

void MainMenuState::initKeybins()
{
	/*std::ifstream ifs("config/mainmenustates_keybins.ini");

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

	for (auto i : this->keybins)
		std::cout << i.first << " " << i.second << std::endl; */
}

void MainMenuState::initButton()
{
	this->buttonTexture["BUTTON"].loadFromFile("button/BUTTON.png");
	this->buttonTexture["BUTTON"].setSmooth(true);

	float width = 175 * 2;
	float height = 66 * 2;
	float x = (this->window->getSize().x / 11.f);
	float y = this->window->getSize().y / 6.f;

	this->buttons["GAME_STATE"] = new gui::Button(&this->buttonTexture["BUTTON"], x *2, y * 4, width, height, 28,
		&this->font, "NEW GAME",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	this->buttons["SCORE_STATE"] = new gui::Button(&this->buttonTexture["BUTTON"], x*6, y * 4, width, height, 28,
		&this->font, "LEADER BOARD",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	this->buttonTexture["EXIT"].loadFromFile("button/incorrect.png");
	this->buttonTexture["EXIT"].setSmooth(true);
	
	x = this->window->getSize().x - 120;
	y = this->window->getSize().y - 120;

	this->buttons["EXIT_STATE"] = new gui::Button(&this->buttonTexture["EXIT"], x, y, 96, 90 , 30,
		&this->font, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack <State*>* states) :
	State(window, supportedKeys, states)
{
	this->initView();

	this->initVariable();
	this->initBackground();
	this->initHighScore();
	this->initHowtoPlay();
	this->initFonts();
	this->initKeybins();
	this->initButton();
	this->initName();

	this->music.openFromFile("map/mainmenu.ogg");
	this->music.setLoop(true);
	this->music.setVolume(100);
	this->music.play();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
		delete it->second;
	delete this->scoreBack;
	delete this->howBack;
}

void MainMenuState::updateInput(const float& deltaTime)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		this->endStates();*/
}

void MainMenuState::updateBackButton()
{
	if (this->scoreBack->isButtonsPressed("BACK"))
	{
		this->scoreBack->initVeriables();
		this->unhighscoreState();
	}
	if (this->howBack->isButtonsPressed("BACK"))
	{
		this->unhowtoplayState();
	}
}

void MainMenuState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New the game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		/*this->states->push(new NameState(this->window, this->supportedKeys, this->states));*/
		this->states->push(new NameState(this->window, this->supportedKeys, this->states, this->music));
	}

	//High Score
	if (this->buttons["SCORE_STATE"]->isPressed())
	{
		this->highscoreState();
	}

	//High Score
	/*if (this->buttons["HOW_STATE"]->isPressed())
	{
		this->howtoplayState();
	}*/

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endStates();
	}
}

void MainMenuState::update(const float& deltaTime, sf::Event sfEven)
{
	this->updateMousePositions(); 
	this->updateInput(deltaTime);

	if (this->music.getVolume() == 0)
		this->music.setVolume(100);

	if (this->highScore)
	{
		this->scoreBack->updatePosition(this->background.getPosition().x, this->background.getPosition().y, static_cast<sf::Vector2f>(this->window->getSize()));
		this->scoreBack->update(this->mousePosView);
		this->updateBackButton();
	}
	else if (this->howtoplay)
	{
		this->howBack->updatePosition(this->background.getPosition().x, this->background.getPosition().y, this->window->getSize().x / 2.0f);
		this->howBack->update(this->mousePosView);
		this->updateBackButton();
	}
	else
		this->updateButtons();

	this->view.setCenter(sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f));
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);

	target->draw(this -> background);
	target->draw(this->logo);
	target->draw(this->me);

	if (this->highScore)
		this->scoreBack->render(*target);
	else if (this->howtoplay)
		this->howBack->render(*target);
	else
		this->renderButtons(*target);

}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

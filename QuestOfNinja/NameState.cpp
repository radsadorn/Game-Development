#include "NameState.h"

void NameState::initKeybins()
{
	/*std::ifstream ifs("config/gamestates_keybins.ini");

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

	for (auto i : this->keybins)*/
	//	std::cout << i.first << " " << i.second << std::endl; 
}

void NameState::initFont()
{
	if (!this->font.loadFromFile("font/EDmuzazhi.ttf"))
		throw("ERROE::MAINMENUSTATE::COUND NOT LOAD FONT");
	if (!this->nameFont.loadFromFile("font/EDmuzazhi.ttf"))
		throw("ERROE::MAINMENUSTATE::COUND NOT LOAD FONT");
}

void NameState::initBackground()
{
	this->backgroundTexture.loadFromFile("background/ENTERNAME.jpeg");
	//this->backgroundTexture.loadFromFile("background/LOADING.png");
	this->backgroundTexture.setSmooth(true);
	this->background.setTexture(&this->backgroundTexture);

	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().y * 700 / 394),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->background.setPosition(sf::Vector2f(this->view.getCenter()));

	this->loadingTexture.loadFromFile("background/LOADING.png");
	this->loadingTexture.setSmooth(true);
	this->loadingBackground.setTexture(&this->loadingTexture);

	this->loadingBackground.setSize(
		sf::Vector2f(
			static_cast<float>(this->window->getSize().y * 1915 / 1072),
			static_cast<float>(this->window->getSize().y)
		)
	);

	this->loadingBackground.setPosition(sf::Vector2f(this->view.getCenter()));
}

void NameState::initNameText()
{
	this->text.setFont(this->nameFont);
	this->text.setCharacterSize(25);
	this->text.setFillColor(sf::Color::White);
	//this->text.setOutlineColor(sf::Color::Black);
	this->text.setLetterSpacing(2);
	//this->text.setOutlineThickness(1);
	this->text.setPosition(this->nameBox.getPosition());

	this->text.setString("tj");
	this->text.setOrigin(sf::Vector2f(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f));
	this->text.setString("");

	this->nameBG.setString("ENTER NAME");
	this->nameBG.setFont(this->nameFont);
	this->nameBG.setCharacterSize(25);
	this->nameBG.setFillColor(sf::Color(255, 255, 255, 150));
	this->nameBG.setOrigin(sf::Vector2f(this->nameBG.getGlobalBounds().width / 2.f, this->nameBG.getGlobalBounds().height / 2.f));
	this->nameBG.setPosition(this->nameBox.getPosition());
}

void NameState::initTextures()
{
	this->texture["PLAYER_SHOW"].loadFromFile("sprite/PNG_PLAYER_1.png");
	this->texture["PLAYER_SOW"].setSmooth(true);

	this->nameboxTexture.loadFromFile("button/namebox.png");
	this->nameboxTexture.setSmooth(true);
	this->nameboxTexture.setSrgb(true);
}

void NameState::initPlayer()
{
	this->body.setSize(sf::Vector2f(125.0f, 110.0f));
	this->body.setScale(this->Scale, this->Scale);
	
	this->body.setOrigin(body.getSize().x / 2.0f, body.getSize().y / 2.0f);
	this->body.setPosition(this->window->getSize().x / 2.f , this->window->getSize().y / 3.f);
	this->body.setTexture(&this->texture["PLAYER_SHOW"]);
	//this->player = new Animation(&this->texture["PLAYER_SHOW"], sf::Vector2u(8,9), 0.1f);
}

void NameState::initButtons()
{
	float width = 96;
	float height = 90;
	float x = this->window->getSize().x / 8 - (width / 2.f) ;
	float y = this->window->getSize().y /7 * 6;

	this->buttonTexture["BACK"].loadFromFile("button/left.png");
	this->buttonTexture["BACK"].setSmooth(true);
	this->buttons["BACK"] = new gui::Button(&this->buttonTexture["BACK"], x, y, width, height, 30,
		&this->font, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	x = this->window->getSize().x / 8 * 7 - (width / 2.f);

	this->buttonTexture["NEXT"].loadFromFile("button/right.png");
	this->buttonTexture["NEXT"].setSmooth(true);

	this->buttons["ENTER"] = new gui::Button(&this->buttonTexture["NEXT"], x, y, width, height, 30,
		&this->font, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));

	x = (this->window->getSize().x / 2.f) - (width / 2.f);
	y = this->window->getSize().y / 7 * 6;

	this->buttonTexture["RANDOM"].loadFromFile("button/reset.png");
	this->buttonTexture["RANDOM"].setSmooth(true);
	
	this->buttons["RANDOM"] = new gui::Button(&this->buttonTexture["RANDOM"], x, y, width, height, 30,
		&this->font, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
}

void NameState::initNameBox()
{
	this->nameBox.setTexture(&this->nameboxTexture);
	this->nameBox.setSize(sf::Vector2f(250 * 1.5, 70 * 1.5));
	this->nameBox.setOrigin(sf::Vector2f(this->nameBox.getSize() / 2.f));
	this->nameBox.setPosition(sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 5.f * 4.f - 20));

	this->cursor.setSize(sf::Vector2f(5, 40));
	this->cursor.setOrigin(sf::Vector2f(this->cursor.getSize() / 2.f));
	this->cursor.setPosition(sf::Vector2f(this->nameBox.getPosition()));
	this->cursor.setFillColor(sf::Color::White);
}

void NameState::initLoading()
{
	this->loading.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	//this->loading.setOrigin(sf::Vector2f(this->loading.getSize().x / 2, this->loading.getSize().y / 2));
	this->loading.setPosition(static_cast<sf::Vector2f>(this->view.getCenter()));
	this->loading.setFillColor(sf::Color(0, 0, 0, 0));

	this->loadingText.setFont(this->font);
	this->loadingText.setString("LOADING...");
	this->loadingText.setCharacterSize(50);
	this->loadingText.setFillColor(sf::Color::Black);
	this->loadingText.setLetterSpacing(3);
	this->loadingText.setOutlineThickness(3);
	this->loadingText.setOutlineColor(sf::Color::White);
	this->loadingText.setOrigin({ this->loadingText.getGlobalBounds().width / 2, this->loadingText.getGlobalBounds().height / 2 });
	this->loadingText.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 7 * 6));
}

NameState::NameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::Music& music):
	State(window, supportedKeys, states), music(music)
{
	this->initView();
	this->initFont();
	this->initTextures();
	this->initPlayer();
	this->initBackground();
	this->initNameBox();
	this->initNameText();
	this->initNameRandom();
	this->initButtons();
	this->initLoading();

	this->namePlayer = ""; 

}

NameState::~NameState()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
		delete it->second;
	delete this->player;

	for (auto& i : this->nameRandom)
		delete &i;
}

void NameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->states->pop();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) and this->namePlayer != "" )
	{
		this->load = true;
	}
}

void NameState::updateDelta()
{
	//Updates the delta variable with the time it takes to update and render one frame.
	this->deltaTime = this->clock.restart().asSeconds();

	if (this->deltaTime >= 1.0f / 20.0f)
		this->deltaTime = 1.0f / 20.0f;
}

void NameState::updateNameBox(sf::Event sfEvent)
{
	if (this->namePlayer == "")
		this->nameBG.setString("ENTER NAME");

	this->totaltimedelete += this->deleteTime.restart().asSeconds();
	if (sfEvent.type == sf::Event::KeyReleased and this->last_char != ' ')
	{
		this->last_char = ' ';
	}

	if (sfEvent.type == sf::Event::TextEntered)
	{
		if (sfEvent.text.unicode == 8)
		{
			this->nameBG.setString("");
			if (this->totaltimedelete > 0.05 and this->namePlayer.length() > 0)
			{
				if (this->nameBG.getString() == "ENTER NAME")
					this->nameBG.setString("");
				this->namePlayer.erase(this->namePlayer.length() - 1);

				this->totaltimedelete = 0;
			}
		}
		else if (this->last_char != sfEvent.text.unicode and
			(
				sfEvent.text.unicode >= 'A' && sfEvent.text.unicode <= 'Z' ||
				sfEvent.text.unicode >= 'a' && sfEvent.text.unicode <= 'z' ||
				sfEvent.text.unicode >= '0' && sfEvent.text.unicode <= '9'
				)
			)
		{
			if (this->nameBG.getString() == "ENTER NAME")
				this->nameBG.setString("");

			if(this->cursor.getPosition().x < this->nameBox.getPosition().x + this->nameBox.getSize().x / 2.f - 60)
				this->namePlayer += sfEvent.text.unicode;
		}

		this->last_char = sfEvent.text.unicode;
	}

	this->text.setString(this->namePlayer);
	this->text.setOrigin(sf::Vector2f(this->text.getGlobalBounds().width / 2.f, this->text.getOrigin().y));
	this->text.setPosition(this->nameBox.getPosition());
	this->cursor.setPosition(sf::Vector2f(this->text.getPosition().x + this->text.getGlobalBounds().width / 2.f , this->text.getPosition().y));
}

void NameState::update(const float& deltaTime, sf::Event sfEven)
{
	if (this->loadingFinish)
	{
		this->states->pop();
		this->states->push(new GameStates(this->window, this->supportedKeys, this->states, this->namePlayer, this->music));
	}
	this->updateMousePositions();
	this->updateInput(deltaTime);
	this->updateDelta();

	this->updateButtons();
	this->updateNameBox(sfEven);

	this->view.setCenter(sf::Vector2f(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f));
}

void NameState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//Enter the name
	if (this->buttons["BACK"]->isPressed() )
	{
		this->states->pop();
	}
	if (this->buttons["ENTER"]->isPressed() and this->namePlayer != "" and this->namePlayer != "ENTER NAME")
	{
		this->load = true;
	}
	if (this->buttons["RANDOM"]->isPressed())
	{
		this->nameBG.setString("");
		this->namePlayer = this->nameRandom[rand() % name];
	}
}

void NameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);

	target->draw(this->background);
	//target->draw(this->body);

	target->draw(this->nameBox);
	
	this->renderCursor(*target);
	this->renderButtons(*target);

	target->draw(this->nameBG);
	target->draw(this->text);
	this->text.setPosition(sf::Vector2f(this->text.getPosition().x + 5, this->text.getPosition().y));

	if (this->load)
	{
		if (this->fade < 255)
			this->fade += 5;
		this->loading.setFillColor(sf::Color(0, 0, 0, this->fade));
		target->draw(this->loading);
		if (this->fade == 255)
		{
			target->draw(this->loadingBackground);
			this->loadingFinish = true;
			target->draw(this->loadingText);
		}
	}
}

void NameState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void NameState::renderCursor(sf::RenderTarget& target)
{
	this->totalTime += time.restart().asSeconds();
	if (this->totalTime >= 0.5)
	{
		this->totalTime = 0.f;
		this->state = !this->state;
	}

	if (this->buttons["RANDOM"]->isPressed())
		this->state = false;
	if(this->last_char == 8)
		this->state = true;

	if (this->state)
	{
		this->text.setPosition(sf::Vector2f(this->text.getPosition().x - 5, this->text.getPosition().y));
		target.draw(this->cursor);
	}
	
}

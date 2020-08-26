#include "GameMain.h"

void GameMain::initVariable()
{
	this->window = NULL;
	this->fullscreen = false;
	this->deltaTime = 0.0f;
}  

void GameMain::initwindow()
{
	std::ifstream ifs("config/window.ini");
	this->VideoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "Quest of Ninja";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if(!this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
	this->window->setKeyRepeatEnabled(true);

}

void GameMain::initKey()
{
	std::ifstream ifs("config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}

	}

	ifs.close();
}

void GameMain::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

GameMain::GameMain() 
{
	this->initwindow();
	this->initStates();	
	this->initKey();
}

GameMain::~GameMain()
{
	//delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void GameMain::endGame()
{
	std::cout << "End Game\n";
}

void GameMain::updateSFMLEvent()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		switch (this->sfEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void GameMain::update()
{
	if (!this->states.empty())
	{
		this->states.top()->update(this->deltaTime, this->sfEvent);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endStates();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endGame();
		this->window->close();
	}
}

void GameMain::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void GameMain::run()
{
	while (this->window->isOpen())
	{
		this->updateSFMLEvent();
		this->update();
		this->render();
	}
}


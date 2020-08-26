#include "State.h"

void State::initView()
{
	this->view = sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
}

void State::initNameRandom()
{
	srand(time(NULL));
	std::ifstream ifs("config/namerandom.ini");

	if (ifs.is_open())
	{
		ifs >> name;

		std::string name = "";

		while (ifs >> name)
		{
			this->nameRandom.push_back(name);
		}

	}

	ifs.close();
}

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys ,std::stack <State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->pause = false;
	this->highScore = false;
	this->howtoplay = false;

}

State::~State()
{
}

const bool& State::getQuit() const
{
	// TODO: insert return statement here
	return this->quit;
}

void State::endStates()
{
	this->quit = true;
}

void State::pauseState()
{
	this->pause = true;
}

void State::unpauseState()
{
	this->pause = false;
}

void State::highscoreState()
{
	this->highScore = true;
}

void State::unhighscoreState()
{
	this->highScore = false;
}

void State::howtoplayState()
{
	this->howtoplay = true;
}

void State::unhowtoplayState()
{
	this->howtoplay = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateInput(const float& deltaTime)
{
}

void State::update(const float& deltaTime,sf::Event sfEven)
{
}

void State::render(sf::RenderTarget* target)
{
}

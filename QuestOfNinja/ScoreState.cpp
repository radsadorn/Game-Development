#include "ScoreState.h"

void ScoreState::initVeriables()
{
	this->countLine = -1;
	this->bar = "";
	this->countText = 0;
}

void ScoreState::initHighScore()
{
}

void ScoreState::initScoreBar()
{
	for (int i = 0; i < 5; ++i)
	{
		this->scoreName[i].setFont(this->font);
		this->scoreName[i].setCharacterSize(20);
		this->scoreName[i].setFillColor(sf::Color::Black);
		this->scoreName[i].setOrigin(sf::Vector2f(this->scoreName[i].getGlobalBounds().width / 2.f, this->scoreName[i].getGlobalBounds().height / 2.f));
		this->scoreName[i].setPosition(
			sf::Vector2f(
				this->paper.getPosition().x + this->paper.getGlobalBounds().width / 4.f * 2.f,
				this->paper.getPosition().y + this->paper.getGlobalBounds().height / 6.f * (i + 1)
			)
		);

		this->scorePoint[i].setFont(this->font);
		this->scorePoint[i].setCharacterSize(20);
		this->scorePoint[i].setFillColor(sf::Color::Black);
		this->scorePoint[i].setOrigin(sf::Vector2f(this->scorePoint[i].getGlobalBounds().width / 2.f, this->scorePoint[i].getGlobalBounds().height / 2.f));
		this->scorePoint[i].setPosition(
			sf::Vector2f(
				this->paper.getPosition().x + this->paper.getGlobalBounds().width / 4.f * 3.f,
				this->paper.getPosition().y + this->paper.getGlobalBounds().height / 6.f * (i + 1)
			)
		);
	}
}


ScoreState::ScoreState(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->buttonTexture.loadFromFile("button/incorrect.png");
	this->buttonTexture.setSmooth(true);

	this->hokangeTexture.loadFromFile("sprite/HOKANGE.png");
	this->hokangeTexture.setSmooth(true);
	this->hokange.setTexture(&this->hokangeTexture);
	this->hokange.setSize(sf::Vector2f(400, 400));
	this->hokange.setOrigin(sf::Vector2f(this->hokange.getSize().x / 2, this->hokange.getSize().x / 2));

	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x - 40.f),
			static_cast<float>(window.getSize().y - 40.f)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x - 100.f),
			static_cast<float>(window.getSize().y - 100.f)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->paper.setSize(
		sf::Vector2f(
			static_cast<float>(window.getSize().x - 200.f),
			static_cast<float>(window.getSize().y - 300.f)
		)
	);
	this->paper.setFillColor(sf::Color(255, 255, 255, 200));

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 255));
	this->menuText.setCharacterSize(72);
	this->menuText.setString("LEADER-BOARD");

	this->initHighScore();
}

ScoreState::~ScoreState()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
		delete it->second;

}

std::map<std::string, gui::Button*>& ScoreState::getButtons()
{
	return this->buttons;
}

const bool ScoreState::isButtonsPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void ScoreState::addButton(const std::string key, float line, int n, const std::string text)
{
	/*float width = 175 * 1.5;
	float height = 66 * 1.5;
	float x = this->container.getPosition().x + (this->container.getSize().x / 2.f) - (width / 2.f);
	float y = line * n;

	this->buttons[key] = new gui::Button(&this->buttonTexture,
		x, y, width, height, 28,
		&this->font, text,
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));*/

	float width = 96;
	float height = 90;
	float x = this->container.getPosition().x + (this->container.getSize().x / 2.f) - (width / 2.f);
	float y = this->container.getPosition().y + (this->container.getSize().y) - (height / 2.f);

	this->buttons[key] = new gui::Button(&this->buttonTexture, x, y, width, height, 30,
		nullptr, "",
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
}

void ScoreState::updatePosition(float x, float y, sf::Vector2f size)
{
	this->background.setPosition(x + 20, y + 20);

	this->container.setPosition(
		sf::Vector2f(
			x + size.x / 2.f - this->container.getSize().x / 2.0f,
			50.0f
		)
	);

	this->paper.setPosition(
		sf::Vector2f(
			x + size.x / 2.f - this->paper.getSize().x / 2.0f,
			size.y / 4.f
		)
	);

	this->hokange.setPosition(
		sf::Vector2f(
			this->paper.getPosition().x + this->paper.getSize().x / 4, 
			this->paper.getPosition().y + this->paper.getSize().y / 2
		)
	);

	this->menuText.setPosition(
		sf::Vector2f(
			this->container.getPosition().x + (this->container.getSize().x / 2.f) - (this->menuText.getGlobalBounds().width / 2.f),
			this->container.getPosition().y + 30
		)
	);
}

void ScoreState::updateHighScore()
{
	std::ifstream ifs("config/highscore.ini");

	if (ifs.is_open())
	{
		std::string name = "";
		int score = 0;

		int i = 0;
		while (ifs >> name >> score and i < 5)
		{
			this->scoreName[i].setString(name);
			this->scorePoint[i].setString(std::to_string(score));
			i++;
		}
	}
	ifs.close();
}

void ScoreState::update(sf::Vector2f& mousePos)
{
	this->updateHighScore();
	this->initScoreBar();

	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
		i.second->setPosition(sf::Vector2f(
			this->container.getPosition().x + (this->container.getSize().x / 2.f) - (i.second->getSize().x / 2.f),
			i.second->getPosition().y
		));
	}

}

void ScoreState::renderScore(sf::RenderTarget& target)
{
	target.draw(this->menuText);

	for (int i = 0; i < countLine; ++i)
	{
		target.draw(this->scoreName[i]);
		target.draw(this->scorePoint[i]);
	}

	this->totalTime += this->clock.restart().asSeconds();
	if (this->bar == this->text)
	{
		if (this->totalTime >= 0.1)
		{
			this->totalTime = 0.f;
			this->countLine++;
		}
	}
	else
	{
		if (this->totalTime >= 0.1)
		{
			this->bar += text[countText++];
			this->totalTime = 0.f;
		}
		this->menuText.setString(bar);
	}

	if (this->countLine > 5)
		this->countLine = 5;
}

void ScoreState::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->paper);

	if (this->countLine == 5)
		for (auto& i : this->buttons)
		{
			i.second->render(target);
		}


	this->renderScore(target);
	target.draw(this->hokange);

}
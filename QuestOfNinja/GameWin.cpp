#include "GameWin.h"

GameWin::GameWin(sf::RenderWindow& window, sf::Font& font, std::string state, std::string namePlayer, int score, bool endgame)
	: font(font)
{
	this->buttonTexture.loadFromFile("button/home.png");
	this->buttonTexture.setSmooth(true);

	this->point = score;
	this->endgame = endgame;

	this->win.setString(state);
	this->win.setFont(this->font);
	this->win.setCharacterSize(180);
	this->win.setOutlineThickness(10);

	this->win.setFillColor(sf::Color(255, 190, 10, 255));
	this->win.setOutlineColor(sf::Color::White);
	this->win.setOrigin(sf::Vector2f(this->win.getGlobalBounds().width / 2.f, 0));

	this->namePlayer.setString(namePlayer);
	this->namePlayer.setFont(this->font);
	this->namePlayer.setCharacterSize(40);
	this->namePlayer.setOutlineThickness(4);

	this->namePlayer.setFillColor(sf::Color::Blue);

	this->namePlayer.setOutlineColor(sf::Color::White);
	this->namePlayer.setOrigin(sf::Vector2f(this->namePlayer.getGlobalBounds().width / 2.f, this->namePlayer.getGlobalBounds().height / 2.f));

	if (state == "MISSION FAIL!!")
	{
		this->win.setFillColor(sf::Color::Red);
	}
	this->win.setPosition(sf::Vector2f(window.getPosition().x + window.getSize().x / 2.f, window.getSize().y / 3.f));

	if (endgame)
	{
		this->namePlayer.setPosition(sf::Vector2f(window.getPosition().x + window.getSize().x / 5.f * 2, window.getSize().y / 5.f * 3));

		this->score.setString(std::to_string(score));
		this->score.setFont(this->font);
		this->score.setCharacterSize(40);
		this->score.setOutlineThickness(4);

		this->score.setFillColor(sf::Color::Blue);

		this->score.setOutlineColor(sf::Color::White);
		this->score.setOrigin(sf::Vector2f(this->score.getGlobalBounds().width / 2.f, this->score.getGlobalBounds().height / 2.f));
		this->score.setPosition(sf::Vector2f(window.getPosition().x + window.getSize().x / 5.f * 4, window.getSize().y / 5.f * 3));
	}
}

GameWin::~GameWin()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
		delete it->second;
}

std::map<std::string, gui::Button*>& GameWin::getButtons()
{
	return this->buttons;
}

const bool GameWin::isButtonsPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameWin::addButton(sf::Texture* texture, const std::string key, float line, int n, int m, const std::string text)
{
	float width = 96.f;
	float height = 90.f;
	float x = this->win.getPosition().x - width / 2;
	float y = line * n;

	this->buttons[key] = new gui::Button(
		&this->buttonTexture,
		x, y, width, height, 30,
		&this->font, text,
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
}

void GameWin::updatePosition(sf::Vector2f pos, sf::Vector2f size)
{
	this->win.setOrigin(sf::Vector2f(this->win.getGlobalBounds().width / 2.f, this->win.getGlobalBounds().height / 2.f));
	this->win.setPosition(sf::Vector2f(pos.x, size.y / 3.f));
	this->namePlayer.setPosition(sf::Vector2f(this->win.getPosition().x, size.y / 5.f * 3));
	if (this->endgame)
	{
		this->namePlayer.setPosition(sf::Vector2f(this->win.getPosition().x - size.x / 7.f, size.y / 5.f * 3));
		this->score.setPosition(sf::Vector2f(this->win.getPosition().x + size.x / 7.f, size.y / 5.f * 3));
	}
}

void GameWin::updateScore()
{
	if (this->endgame)
	{
		this->pointUpdate += rand() % 20 + 40;
		if (this->pointUpdate > this->point)
			this->pointUpdate = this->point;
		this->score.setString(std::to_string(this->pointUpdate));
		this->score.setOrigin(sf::Vector2f(this->score.getGlobalBounds().width / 2.f, this->score.getGlobalBounds().height / 2.f));
	}
}

void GameWin::update(sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
		i.second->setPosition(sf::Vector2f(
			this->win.getPosition().x - (i.second->getSize().x / 2.f),
			i.second->getPosition().y
		));
	}
}

void GameWin::render(sf::RenderTarget& target)
{
	target.draw(this->win);
	target.draw(this->namePlayer);
	if (this->endgame)
	{
		target.draw(this->score);
	}

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

}

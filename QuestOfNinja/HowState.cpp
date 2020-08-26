#include "HowState.h"

HowState::HowState(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->buttonTexture.loadFromFile("button/incorrect.png");
	this->buttonTexture.setSmooth(true);

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

	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(72);
	this->menuText.setString("HOW TO PLAY");
}

HowState::~HowState()
{
	auto it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
		delete it->second;
}

std::map<std::string, gui::Button*>& HowState::getButtons()
{
	return this->buttons;
}

const bool HowState::isButtonsPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void HowState::addButton(const std::string key, float line, int n, const std::string text)
{
	float width = 175 * 1.5;
	float height = 66 * 1.5;
	float x = this->container.getPosition().x + (this->container.getSize().x / 2.f) - (width / 2.f);
	float y = line * n;

	this->buttons[key] = new gui::Button(&this->buttonTexture,
		x, y, width, height, 30,
		&this->font, text,
		sf::Color::White, sf::Color(125, 125, 125, 255), sf::Color(100, 100, 100, 255));
}

void HowState::updatePosition(float x, float y, float z)
{
	this->background.setPosition(x + 20, y + 20);

	this->container.setPosition(
		sf::Vector2f(
			x + z - this->container.getSize().x / 2.0f,
			50.0f
		)
	);

	this->menuText.setPosition(
		sf::Vector2f(
			this->container.getPosition().x + (this->container.getSize().x / 2.f) - (this->menuText.getGlobalBounds().width / 2.f),
			this->container.getPosition().y + 30
		)
	);
}

void HowState::update(sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
		i.second->setPosition(sf::Vector2f(
			this->container.getPosition().x + (this->container.getSize().x / 2.f) - (i.second->getSize().x / 2.f),
			i.second->getPosition().y
		));
	}
}

void HowState::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}

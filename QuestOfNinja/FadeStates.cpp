#include "FadeStates.h"

FadeStates::FadeStates(sf::Vector2u size, sf::Vector2f pos)
{
	this->fadeBox.setSize(sf::Vector2f(size.x, size.y));
	this->fadeBox.setOrigin(this->fadeBox.getSize() / 2.f);
	this->fadeBox.setPosition(sf::Vector2f(pos.x + size.x / 2.f, size.y / 2.f));
}

FadeStates::~FadeStates()
{
}

void FadeStates::updateState(int fade, int minmax)
{
	this->fademinmax = fade;
	this->minmax = minmax;
}

void FadeStates::updateFadeBox()
{
	if (this->fade == minmax)
		this->fade = minmax;
	else
		this->fade += fade;

	this->fadeBox.setFillColor(sf::Color(10, 10, 10, this->fade));
}

void FadeStates::updatePosition(sf::Vector2u size, sf::Vector2f pos)
{
	this->fadeBox.setPosition(sf::Vector2f(pos.x + size.x / 2.f, size.y / 2.f));
}

void FadeStates::render(sf::RenderTarget& target)
{
	target.draw(this->fadeBox);
}

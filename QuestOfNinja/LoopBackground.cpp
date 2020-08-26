#include "LoopBackground.h"

LoopBackground::LoopBackground(sf::Texture* texture, sf::Vector2f size)
{
	texture->setRepeated(true);
	this->background.setSize(size);
	this->background.setTexture(texture);
	//this->background.setOrigin(size / 2.f);
}

LoopBackground::~LoopBackground()
{
}

void LoopBackground::setPosition(sf::Vector2f pos)
{
	this->background.setPosition(pos);
}

void LoopBackground::setTextureRect(sf::IntRect uvRect)
{
	this->background.setTextureRect(uvRect);
}

void LoopBackground::render(sf::RenderTarget& target)
{
	target.draw(this->background);
}

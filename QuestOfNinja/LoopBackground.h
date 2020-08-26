#pragma once

#include "SFML/Graphics.hpp"

class LoopBackground
{
public:
	LoopBackground(sf::Texture* texture, sf::Vector2f size);
	~LoopBackground();

	void setPosition(sf::Vector2f pos);
	void setTextureRect(sf::IntRect uvRect);
	void render(sf::RenderTarget& target);

	sf::Vector2f getPosition() { return this->background.getPosition(); };

private:
	sf::RectangleShape background;
};


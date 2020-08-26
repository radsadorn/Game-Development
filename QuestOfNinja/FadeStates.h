#pragma once

#include "SFML/Graphics.hpp"

class FadeStates
{
public:
	FadeStates(sf::Vector2u size, sf::Vector2f pos);
	~FadeStates();

	sf::Vector2f getPosition() { return this->fadeBox.getPosition(); };
	sf::Vector2f getSize() { return this->fadeBox.getSize(); };

	void updateState(int fade, int minmax);
	void updateFadeBox();
	void updatePosition(sf::Vector2u size, sf::Vector2f pos);
	void render(sf::RenderTarget& target);

	int fade = 0;

private:
	sf::RectangleShape fadeBox;
	int fademinmax;
	int minmax;
	
};


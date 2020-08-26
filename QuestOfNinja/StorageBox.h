#pragma once

#include "SFML/Graphics.hpp"

class StorageBox
{
public:
	StorageBox(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos);
	~StorageBox();

private:
	sf::RectangleShape box;
	sf::RectangleShape item;
};


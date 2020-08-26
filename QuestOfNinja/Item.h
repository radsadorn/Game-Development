#pragma once

#include "SFML/Graphics.hpp"
#include "HitboxComponent.h"
#include "Collider.h"

class Item
{
public:
	Item(sf::Texture* texture, int checkItem, sf::Vector2f size, sf::Vector2f position);
	~Item();

	Collider GetCollider() { return Collider(this->item); }

	void onCollision(sf::Vector2f direction);

	bool getStatus() { return this->show; }
	int getItem() { return this->checkItem; };

	void update(float deltaTime);
	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape item;

	sf::Vector2f velocity;

	sf::Clock clock;
	sf::Clock time;

	float totalTime = 0.f;
	float showtime = 0.f;

	bool state = true;
	bool status = true;
	bool show = true;

	int checkItem;

};


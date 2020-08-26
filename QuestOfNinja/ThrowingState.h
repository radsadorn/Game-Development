#pragma once

#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Collider.h"

class ThrowingState
{
public:
	ThrowingState(sf::Texture* texture, sf::Vector2f pos, sf::Vector2u imageCount, int row, int colum, float switchTime, float velocityx, int power);
	~ThrowingState();

	Collider GetCollider() { return Collider(this->body); }

	int getPower() { return this->power; }
	float getVeclocity() { return this->velocity.x; };
	void onCollision(sf::Vector2f direction);

	void update(float deltaTime);
	void render(sf::RenderTarget* target);

private:
	Animation animation;
	sf::RectangleShape body;
	sf::RectangleShape box;

	sf::Vector2f velocity;
	float deceleration = 4.f;

	int row;
	int colum;
	int power;
};


#pragma once

#include "SFML/Graphics.hpp"
#include "Collider.h"

class HitboxEnemy
{
public:
	HitboxEnemy(sf::Vector2f size);
	~HitboxEnemy();

	void move(sf::Vector2f move, float deltaTime);
	void Draw(sf::RenderTarget* target);
	void setPosition(sf::Vector2f pos) { this->hitbox.setPosition(pos); };
	void setScale(sf::Vector2f scale) { this->hitbox.setScale(scale); };

	sf::Vector2f getPosition() { return hitbox.getPosition(); }
	Collider GetCollider() { return Collider(this->hitbox); }

private:
	sf::RectangleShape hitbox;
};


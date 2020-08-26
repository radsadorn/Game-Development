#pragma once

#include "SFML/Graphics.hpp"
using namespace sf;

class Collider
{
public:
	Collider(RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { this->body.move(dx, dy); }

	bool CheckCollisionThrowing(Collider other, Vector2f& direction);
	bool CheckCollision(Collider other,Vector2f& direction, float& hit, float push);
	bool CheckCollisionSwordEnemy(Collider other, Vector2f& direction, float& hit, float push);
	bool CheckCollisionPlatform(Collider other, Vector2f& direction, float push);
	bool CheckCollisionItem(Collider other, Vector2f& direction, float push);
	sf::Vector2f GetPosition() { return this->body.getPosition(); }
	sf::Vector2f GetHalfSize() { return this->body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
};


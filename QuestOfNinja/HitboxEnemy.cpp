#include "HitboxEnemy.h"

HitboxEnemy::HitboxEnemy(sf::Vector2f size)
{
	this->hitbox.setSize(size);
	this->hitbox.setOrigin(sf::Vector2f(size.x * 1.5f, size.y / 2.f));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(2);
	this->hitbox.setOutlineColor(sf::Color::Magenta);
}

HitboxEnemy::~HitboxEnemy()
{
}

void HitboxEnemy::move(sf::Vector2f move, float deltaTime)
{
	this->hitbox.move(move * deltaTime);
}

void HitboxEnemy::Draw(sf::RenderTarget* target)
{
	target->draw(hitbox);
}
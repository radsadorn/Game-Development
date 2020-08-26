#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Vector2f pos, sf::Vector2f size)
{
	this->hitbox.setSize(size);
	this->hitbox.setPosition(pos);
	this->hitbox.setOrigin(size / 2.f);
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(2);
	this->hitbox.setOutlineColor(sf::Color::Magenta);
}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::move(sf::Vector2f move)
{
	this->hitbox.move(move);
}

void HitboxComponent::Draw(sf::RenderTarget* target)
{
	target->draw(hitbox);
}
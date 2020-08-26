#include "Item.h"

Item::Item(sf::Texture* texture, int checkItem, sf::Vector2f size, sf::Vector2f position)
{
	this->item.setTexture(texture);
	this->item.setSize(size);
	this->item.setOrigin(size / 2.f);
	this->item.setPosition(position);
	this->checkItem = checkItem;
}

Item::~Item()
{
}

void Item::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom
		velocity.y = 0.0f;
		//canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}
}

void Item::update(float deltaTime)
{
	this->velocity.y += 981.0f * deltaTime;
	if (this->velocity.y <= 0.f)
		this->velocity.y = -sqrt(2.0f * 981.0f * 50.f);

	this->totalTime += this->clock.restart().asSeconds();
	if (this->totalTime > 8.f)
		this->status = false;

	if (this->totalTime > 10.f)
		this->show = false;

	this->velocity.x = 0;
	this->item.move(this->velocity * deltaTime);
}

void Item::render(sf::RenderTarget& target)
{
	this->showtime += this->time.restart().asSeconds();
	if (this->totalTime > 8.f)
		if (this->showtime >= 0.1)
		{
			this->showtime = 0.f;
			this->state = !this->state;
		}
	if (this->state)
		target.draw(this->item);
}

#include "ThrowingState.h"

ThrowingState::ThrowingState(sf::Texture* texture, sf::Vector2f pos, sf::Vector2u imageCount, int row, int colum, float switchTime, float velocityx, int power)
	: animation(texture, imageCount, switchTime)
{
	this->body.setTexture(texture);
	this->body.setSize(sf::Vector2f(100, 100));
	this->body.setOrigin(sf::Vector2f(this->body.getSize().x / 2, this->body.getSize().y / 2));
	this->body.setPosition(pos);
	this->velocity.x = velocityx;
	this->power = power;

	this->row = row;
	this->colum = colum;

	//printf("position %f %f\n", pos.x, pos.y);
}

ThrowingState::~ThrowingState()
{
}

void ThrowingState::update(float deltaTime)
{
	if (this->velocity.x > 0.0)
	{
		this->velocity.x -= this->deceleration;
		if (this->velocity.x <= 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.0)
	{
		this->velocity.x += this->deceleration;
		if (this->velocity.x >= 0.f)
			this->velocity.x = 0.f;
	}

	//this->velocity.y += 9.81f * deltaTime;

	this->animation.Update(this->row, this->colum, deltaTime, true);
	this->body.setTextureRect(this->animation.spriteRect);
	this->body.move(this->velocity * deltaTime);
	//printf("%f %f\n", this->body.getPosition().x, this->body.getPosition().y);
}

void ThrowingState::render(sf::RenderTarget* target)
{
	target->draw(this->body);
}

void ThrowingState::onCollision(sf::Vector2f direction)
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


#include "Entity.h"

void Entity::initVariable()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movementSpeed = 100.f;
}

Entity::Entity()
{
	
	this->movementSpeed = 100.0f;
}

Entity::~Entity()
{
	this->initVariable();
	delete this->sprite;
}

//Component FT
void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}

//Function

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x,y);
	}
}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y)
{
	if (this->sprite)
	{
		this->sprite->move(dir_x * this->movementSpeed * deltaTime, dir_y * this->movementSpeed * deltaTime);
	}
}

void Entity::update(const float& deltaTime)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if(this->sprite)
		target->draw(*this->sprite);
}

#include "Body.h"

Body::Body(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->row = 0;
	this->faceRight = true;
	this->jumpHeight = jumpHeight;

	this->hitbox = new HitboxComponent(sf::Vector2f(1000, 300), sf::Vector2f(60, 100));

	this->body.setSize(sf::Vector2f(125.0f, 110.0f));
	//body.setPosition(groundHeight, groundHeight- body.getSize().y);
	this->body.setTexture(texture);
	this->body.setOrigin(body.getSize().x / 2.0f , body.getSize().y / 2.0f + 15);
	this->body.setScale(Scale, Scale);

	this->buffer.loadFromFile("map/sound-381.ogg");
	this->sound.setBuffer(buffer);
	this->sound.setVolume(100);
}

Body::~Body()
{
}

int Body::updateAction()
{
	return this->row;;
}

bool Body::getAttack()
{
	if (animation.currentImage.x == this->colum / 2)
	{
		if (!this->checkAttack)
		{
			this->checkAttack = true;
			//return this->power;
		}
	}
	else
	{
		this->checkAttack = false;
	}

	return this->checkAttack;
}

void Body::updateHurt(sf::Vector2f otherPos)
{
	this->totaltimehurt += this->clockHurt.restart().asSeconds();
	if (!this->hurt and this->totaltimehurt > 1.f and this->canAttack and this->canJump)
	{
		this->row = 2; this->colum = 7;
		this->animation.currentImage.x = 0;
		this->hurt = true;

		if (otherPos.x > this->body.getPosition().x)
		{
			this->velocity.x -= 10000;
			this->body.setScale(this->Scale, this->Scale);
		}
		else
		{
			this->velocity.x += 10000;
			this->body.setScale(-this->Scale, this->Scale);
		}

		this->totaltimehurt = 0;
		this->clockHurt.restart().asSeconds();
	}
}

void Body::Update(float deltaTime, bool win, float limit, int& mana)
{
	this->Keep = true;

	//Throw row = 5 colum = 8

	//Die row = 2 colum = 5

	//Update skill
	float time = this->clock.restart().asSeconds();
	this->st_skill -= time;
	this->nd_skill -= time;
	this->rd_skill -= time;

	if (this->st_skill <= 0)
		this->st_skill = 0;
	if (this->nd_skill <= 0)
		this->nd_skill = 0;
	if (this->rd_skill <= 0)
		this->rd_skill = 0;

	this->totaltimehurt += this->clockHurt.restart().asSeconds();

	if (!this->die and !this->hurt)
	{
		//Attack
		if (this->canAttack == false)
		{
			if (this->animation.currentImage.x == this->attack) {
				this->canAttack = true;
				this->attack = 0;
			}
			if (this->sound.getStatus() == 0)
				this->sound.play();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) and this->canAttack and this->canJump)
		{
			if (this->st_skill == 0 and mana >= 3)
			{
				this->animation.currentImage.x = 0;
				this->canAttack = false;
				this->row = 6; this->colum = 7;
				this->attack = 6;

				//time
				this->st_skill = 3;
				mana -= 3;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) and this->canAttack and this->canJump)
		{
			if (this->nd_skill == 0.f and mana >= 5)
			{
				this->animation.currentImage.x = 0;
				this->canAttack = false;
				this->row = 7; this->colum = 7;
				this->attack = 6;

				//time
				this->nd_skill = 5;
				mana -= 5;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) and this->canAttack and this->canJump)
		{
			this->hurt = false;
			if (this->rd_skill == 0.f and mana >= 10)
			{
				this->animation.currentImage.x = 0;
				this->canAttack = false;
				this->row = 8; this->colum = 8;
				this->attack = 7;

				//time
				this->rd_skill = 10;
				mana -= 10;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) and this->canAttack and this->canJump)
		{
			this->animation.currentImage.x = 0;
			this->canAttack = false;
			this->row = 5; this->colum = 8;
			this->attack = 7;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U) and this->canAttack and this->canJump)
		{
			this->animation.currentImage.x = 0;
			this->canAttack = false;
			this->row = 5; this->colum = 8;
			this->attack = 7;
		}

		//Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and this->canJump and this->canAttack)
		{
			this->Keep = false;
			this->row = 4; this->colum = 2;
			this->velocity.x = 0.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and this->Keep and this->canAttack)
		{
			if (this->hitbox->getPosition().x > 500.f and this->hitbox->getPosition().x > limit)
				this->velocity.x -= 1.f * this->accelaration;
			this->body.setScale(-this->Scale, this->Scale);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and this->Keep and this->canAttack)
		{
			if (this->hitbox->getPosition().x < 13600.f)
				this->velocity.x += 1.f * this->accelaration;
			this->body.setScale(this->Scale, this->Scale);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and this->canJump and this->Keep and this->canAttack)
		{
			this->canJump = false;
			this->row = 5; this->colum = 7;
			//square root (2.0f * gravity * jumpHeight)
			this->velocity.y = -sqrt(2.0f * 981.0f * this->jumpHeight);
		}

		//Update Movement
		if (this->velocity.x == 0.0f and this->canJump and this->Keep and this->canAttack)
		{
			this->row = 0; this->colum = 4;
		}
		if (this->velocity.x != 0.0f and this->canJump and this->Keep and this->canAttack and !this->hurt)
		{
			this->row = 3; this->colum = 6;
		}

		//Velocity
	}
	else if (this->hurt)
	{
		if (this->animation.currentImage.x == this->colum - 2)
		{
			this->hurt = false;
		}
	}

	if (this->hitbox->getPosition().x < limit - 50 and velocity.x < 0)
		this->velocity.x = 0.f;

	this->velocity.y += 981.0f * deltaTime;
	if (this->velocity.x > 0.0)
	{
		if (this->velocity.x >= this->maxVelocity)
			this->velocity.x = this->maxVelocity;
		this->velocity.x -= this->deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.0)
	{
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
		this->velocity.x += this->deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	//End game
	if (win)
	{
		this->velocity.x = 0;
	}

	if (this->die and !this->dying)
	{
		this->animation.currentImage.x = 0;
		this->dying = true;
	}

	if (this->die)
	{
		this->row = 1; this->colum = 6;
		if (this->animation.currentImage.x == this->colum - 1)
			this->animation.currentImage.x = this->colum - 2;
	}
	
	this->animation.Update(this->row, this->colum, deltaTime, this->faceRight);

	if (!this->die)
		this->body.setTextureRect(this->animation.spriteRect);
	else if (this->die and this->animation.currentImage.x != this->colum - 1)
		this->body.setTextureRect(this->animation.spriteRect);

	this->hitbox->move(this->velocity * deltaTime);
	this->body.setPosition({ this->hitbox->getPosition().x + 3, this->hitbox->getPosition().y });
}

void Body::Draw(sf::RenderTarget* target)
{
	target->draw(body);
	//this->hitbox->Draw(target);
}

void Body::onCollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}
}
#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Animation.h"
#include "Collider.h"
#include "HitboxComponent.h"

using namespace sf;

class Body
{
public:
	Body(Texture* texture, Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Body();

	int updateAction();
	bool getAttack();

	sf::Vector2f getScale() { return this->body.getScale(); };
	float getCountdown_stSkill() { return this->st_skill; };
	float getCountdown_ndSkill() { return this->nd_skill; };
	float getCountdown_rdSkill() { return this->rd_skill; };

	bool getHurt() { return this->hurt; }
	void updateHurt(sf::Vector2f otherPos);
	void Update(float deltaTime, bool win, float limit, int& mana);
	void Draw(sf::RenderTarget* target);
	void onCollision(Vector2f direction);

	void setPosition(sf::Vector2f Pos) { this->hitbox->setPosition(Pos);  };

	Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return this->hitbox->GetCollider(); }

	bool die = false;

private:
	RectangleShape body;
	Animation animation;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	HitboxComponent* hitbox;

	//Movement
	unsigned int row;
	float speed;
	bool faceRight;
	const float Scale = 2.0f;
	const float groundHeight = 300.0;

	Vector2f velocity;
	bool canJump;
	bool Keep;
	float jumpHeight;
	int colum;
	bool canAttack = true;
	int attack ;
	bool checkAttack = false;

	//Hurt
	bool hurt = false;
	sf::Clock clockHurt;
	float totaltimehurt = 0;

	float maxVelocity = 300;
	float accelaration = 15;
	float deceleration = 5;

	//Skill
	sf::Clock clock;
	float st_skill = 0;
	float nd_skill = 0;
	float rd_skill = 0;

	//Die
	bool dying = false;

	//Throwing 
	bool throwing = false;

	
};


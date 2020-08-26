#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Collider.h"
#include "math.h"
#include "windows.h"
#include "time.h"
#include "HitboxComponent.h"
#include "HitboxEnemy.h"

#include "iostream"

class Monster
{
public:
	Monster(sf::Texture* texture, sf::Vector2f pos, sf::Vector2u imageCount, sf::Vector2f size, 
		int colum, float switchTime, float speed, float dis, int HP, int point, int power);
	~Monster();

	void updateDamage(int damage);
	void Update(float deltaTime, sf::Vector2f pos, int hit, bool playerdie);
	void Draw(sf::RenderTarget& target);
	void onCollision(sf::Vector2f direction);
	void move(sf::Vector2f mov) { this->hitbox->move(mov); };

	int updateAttack();
	float updateHp(float hit);
	int updateScore() { return this->point; };

	int getPower() { return this->power; };
	bool getAttack();
	bool checkDie() { return deleteMonster; };

	void setPosition(sf::Vector2f pos) { this->hitbox->setPosition(pos); };

	sf::Vector2f getScale() { return this->body.getScale(); };
	sf::Vector2f getPosition() { return this->hitbox->getPosition(); }
	Collider GetCollider() { return this->hitbox->GetCollider(); }
	Collider GetColliderSword() { return this->sword->GetCollider(); }


private:
	sf::RectangleShape body;
	sf::CircleShape shape;
	Animation animation;

	sf::RectangleShape sss;

	HitboxComponent* hitbox;
	HitboxEnemy* sword;;

	int row;
	int colum;
	const float Scale = 1.0f;

	//Movement
	float speed ;
	bool canJump;
	sf::Vector2f velocity;
	sf::Vector2f Pos;
	bool walk = true;
	float jumpHeight = 100;
	float dis;

	float maxVelocity = 200;
	float accelaration = 10;
	float deceleration = 1;

	//HP
	int HP;
	sf::Text damage;
	int fadeDamage = 255;

	//Power
	int power;
	bool checkAttack = false;
	bool attackStatus = false;

	//Hurt
	bool hurt = false;
	sf::Clock clockHurt;
	float totaltimehurt = 0;

	float size;
	float totalTime;
	sf::Clock time;
	bool state = true;

	bool die = false;
	bool deleteMonster = false;
	bool out = false;
	int fade = 250;
	int point;

	int k;

	sf::Font font;
	sf::Text text;
	sf::Text bgText;

	//Attack
	sf::Clock clockAttack;
	float totaltimeattack = 0;

};


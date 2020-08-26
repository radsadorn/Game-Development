#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Animation.h"
#include "Body.h"
#include "iostream"
#include "Platform.h"

#include "ctime"
#include "cstdlib"
#include "fstream"
#include "sstream"
#include "stack"
#include "map"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	//Component Functions
	void createSprite(sf::Texture* texture);

	//Function
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& deltaTime, const float dir_x, const float dir_y);

	virtual void update(const float& deltaTime) ;
	virtual void render(sf::RenderTarget* target) ;

private:
	void initVariable();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	float movementSpeed;

};

#pragma once

#include "Entity.h"

class Player :
	public Entity
{
public:
	Player(float x, float y, sf::Texture* texture);
	~Player();

private:
	void initVariable();
	void initComponents();
};


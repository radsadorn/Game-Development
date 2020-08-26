#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation
{
public:
	Animation(Texture* texture,  Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, int colum, float deltaTime, bool faceRight);

private:

public:
	IntRect spriteRect;
	Vector2u currentImage;

private:
	Vector2u imageCount;

	float totalTime;
	float switchTime;

};


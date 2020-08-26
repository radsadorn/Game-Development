#include "Animation.h"

Animation::Animation(Texture* texture,  Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	spriteRect.width  = texture->getSize().x / float(imageCount.x);
	spriteRect.height = texture->getSize().y / float(imageCount.y);

}

Animation::~Animation()
{

}

void Animation::Update(int row, int colum , float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= colum)
		{
			currentImage.x = 0;
		}
	}

	spriteRect.top = currentImage.y * spriteRect.height;

		spriteRect.left = currentImage.x * spriteRect.width;
		spriteRect.width = spriteRect.width;

	//spriteRect.left = currentImage.x * spriteRect.width;
	//spriteRect.top = currentImage.y * spriteRect.height;
}

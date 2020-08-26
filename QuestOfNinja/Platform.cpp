#include "Platform.h"

Platform::Platform(Texture* texture, Vector2f size, Vector2f position)
{
	body.setSize(size);
	body.setFillColor(sf::Color(200, 200, 200, 255));
	body.setOrigin(Vector2f(size.x / 2.0f , size.y / 2.f));
	body.setTexture(texture);
	body.setPosition(position);
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderTarget* target)
{
	target->draw(body);
}

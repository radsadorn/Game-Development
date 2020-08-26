#include "Button.h"

gui::Button::Button(sf::Texture* texture, float x, float y, float width, float height, int size, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	//this->buttonTexture.loadFromFile("Acc/5.png");

	this->buttonState = BTN_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setTexture(texture);
	//this->shape.setTextureRect(sf::IntRect(0, 0, 440, 160));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(size);
	this->text.setOrigin(sf::Vector2f(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2));
	this->text.setPosition(sf::Vector2f(
		this->shape.getPosition().x  + (this->shape.getGlobalBounds().width / 2.f + 40), 
		this->shape.getPosition().y  + (this->shape.getGlobalBounds().height / 2.f )
	));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	//this->shape.setFillColor(this->idleColor);
}

gui::Button::~Button()
{
}

//Accessssors

const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

//Function
void gui::Button::setPosition(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
	//this->text.setOrigin(sf::Vector2f(0, this->text.getGlobalBounds().height / 2));
	this->text.setOrigin(sf::Vector2f(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2));
	/*this->text.setPosition(sf::Vector2f(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f)
	));*/

	this->text.setPosition(sf::Vector2f(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f + 40),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)
	));
}

void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:		//this->shape.setScale(1, 1); break;
		this->shape.setFillColor(this->idleColor);		break;

	case BTN_HOVER:		//this->shape.setScale(1.1, 1.1); break;
		this->shape.setFillColor(this->hoverColor);		break;

	case BTN_ACTIVE:	//this->shape.setScale(0.9, 0.9); break;
		this->shape.setFillColor(this->activeColor);	break;

	default:			this->shape.setFillColor(sf::Color::Red);		break;
	}

	//this->shape.setOrigin(sf::Vector2f(this->shape.getSize().x / 2, this->shape.getSize().y / 2));
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

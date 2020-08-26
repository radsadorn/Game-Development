#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "iostream"
#include "ctime"
#include "cstdlib"
#include "sstream"

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};


namespace gui
{
	class Button
	{
	public:
		Button(sf::Texture* texture, float x, float y, float width, float height, int size,
			sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~Button();

		//Accessssors
		const bool isPressed() const;

		//Function
		sf::Vector2f getPosition() { return this->shape.getPosition(); };
		sf::Vector2f getSize() { return this->shape.getSize(); };
		void setPosition(sf::Vector2f pos);
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	private:
		short unsigned buttonState;

		sf::Texture buttonTexture;
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	};
}


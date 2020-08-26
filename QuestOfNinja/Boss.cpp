#include "Boss.h"

Boss::Boss(
	sf::Texture* texture, sf::Vector2f pos,
	sf::Vector2u imageCount, sf::Vector2f size,
	int colum, float switchTime, float speed,
	float dis, int HP, int point, int power) :

	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->dis = dis;
	this->Pos = pos;
	this->colum = colum;
	this->HP = HP;
	this->point = point;
	this->power = power;
	this->font.loadFromFile("font/EDmuzazhi.ttf");
	this->text.setCharacterSize(25);
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::Red);
	this->text.setOutlineThickness(2);
	this->text.setOutlineColor(sf::Color::Black);

	this->pos = pos;

	this->sss.setSize({ 40,40 });
	this->sss.setPosition({ 2000, 300 });

	this->hitbox = new HitboxComponent(pos, size);
	this->size = texture->getSize().x / imageCount.x * (colum - 2);

	this->body.setSize(size * 2.f);
	this->body.setPosition(pos);
	this->body.setTexture(texture);
	this->body.setOrigin(this->body.getSize().x / 2.0f, this->body.getSize().x / 2.0f);
	this->body.setScale(this->Scale, this->Scale);
	this->body.setFillColor(sf::Color::Red);

	this->sword = new HitboxEnemy(sf::Vector2f(60, 80));
}

Boss::~Boss()
{
}

int Boss::updateAttack()
{
	return this->row;
}

void Boss::updateDamage(int damage)
{
	this->fadeDamage = 255;

	this->damage.setString(std::to_string(damage));
	this->damage.setOrigin(sf::Vector2f(this->damage.getGlobalBounds().width / 2.f, 0));
	this->damage.setFont(this->font);
	this->damage.setCharacterSize(30);
	this->damage.setFillColor(sf::Color(255, 200, 0, this->fadeDamage));
	this->damage.setOutlineColor(sf::Color::White);
	this->damage.setOutlineThickness(3);
	this->damage.setPosition(sf::Vector2f(this->body.getPosition().x, this->body.getPosition().y - 100.f));
}

void Boss::Update(float deltaTime, sf::Vector2f pos, int hit, bool playerdie)
{
	this->velocity.x = 0;
	this->velocity.y += 981.0f * deltaTime;

	this->totaltimeattack += this->clockAttack.restart().asSeconds();

	//Dying
	if (hit < 0)
	{
		if (!this->die)
			this->animation.currentImage.x = 0;

		this->row = 0;
		this->die = true;

		if (this->animation.currentImage.x == this->colum - 2)
			this->out = true;

		this->body.setFillColor(sf::Color(200, 200, 200, this->fade -= 5));
		if (this->fade <= 0)
			this->deleteMonster = true;

		this->attackStatus = false;
	}

	//Not die
	if (!this->die)
	{
		if (hit != 0)
		{
			this->animation.currentImage.x = 0;
			this->row = 1;

			this->hurt = true;
			if (this->getPosition().x > pos.x and this->body.getPosition().x < this->pos.x + 600)
				this->velocity.x += hit * 20;
			if (this->getPosition().x < pos.x and this->body.getPosition().x > this->pos.x - 600)
				this->velocity.x -= hit * 20;

			this->totaltimehurt = 0;
			this->clockHurt.restart().asSeconds();

			this->attackStatus = false;
		}

		if (this->attackStatus)
		{
			this->row = 3;
			if (this->animation.currentImage.x == this->colum - 1)
				this->attackStatus = false;
		}
		//Hurt
		else if (this->hurt)
		{
			if (this->animation.currentImage.x == this->colum - 1)
				this->animation.currentImage.x = this->colum - 2;

			this->totaltimehurt += this->clockHurt.restart().asSeconds();
			if (this->totaltimehurt > 0.5f)
				this->hurt = false;

		}
		else if (abs(this->body.getPosition().y - pos.y) < 250 and abs(this->body.getPosition().x - pos.x) < 500 and abs(this->body.getPosition().x - pos.x) > this->dis)
		{
			this->row = 2;
			if (this->body.getPosition().x > pos.x)
			{
				this->velocity.x -= this->speed;
				this->body.setScale(-this->Scale, this->Scale);
				this->sword->setScale(sf::Vector2f(this->Scale, this->Scale));
			}
			if (this->body.getPosition().x < pos.x)
			{
				this->velocity.x += this->speed;
				this->body.setScale(this->Scale, this->Scale);
				this->sword->setScale(sf::Vector2f(-this->Scale, this->Scale));
			}
			if (this->body.getPosition().y > pos.y and this->canJump and abs(this->body.getPosition().x - pos.x) < 250)
			{
				this->canJump = false;
				this->velocity.y = -sqrt(2.0f * 981.0f * this->jumpHeight);
			}
		}
		else if (abs(this->body.getPosition().x - pos.x) < this->dis and abs(this->body.getPosition().y - pos.y) < 50 and this->totaltimeattack > 0.5f and !playerdie)
		{
			this->row = 3;
			if (this->body.getPosition().x > pos.x)
			{
				this->body.setScale(-this->Scale, this->Scale);
				this->sword->setScale(sf::Vector2f(this->Scale, this->Scale));
			}
			if (this->body.getPosition().x < pos.x)
			{
				this->body.setScale(this->Scale, this->Scale);
				this->sword->setScale(sf::Vector2f(-this->Scale, this->Scale));
			}

			this->attackStatus = true;
			this->animation.currentImage.x = 0;

			this->totaltimeattack = 0;
		}
		else
		{
			this->row = 2;
			if (walk) {
				this->velocity.x -= this->speed;
				this->body.setScale(-this->Scale, this->Scale);
				this->sword->setScale(sf::Vector2f(this->Scale, this->Scale));
			}
			else
			{
				this->velocity.x += this->speed;
				this->body.setScale(this->Scale, this->Scale);
				this->sword->setScale(sf::Vector2f(-this->Scale, this->Scale));
			}

			if (this->getPosition().x > this->Pos.x + 250)
				this->walk = true;
			if (this->getPosition().x < this->Pos.x - 250)
				this->walk = false;
		}
	}

	this->animation.Update(this->row, this->colum, deltaTime, true);

	//Dying
	if (this->out)
		this->animation.currentImage.x = this->colum - 2;

	this->body.setTextureRect(this->animation.spriteRect);
	this->hitbox->move(this->velocity * deltaTime);
	this->body.setPosition(this->hitbox->getPosition());

	this->sword->setPosition(this->hitbox->getPosition());

	this->text.setString(std::to_string(this->HP));
	this->text.setOrigin({ this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f });
	this->text.setPosition(sf::Vector2f(this->hitbox->getPosition().x, this->hitbox->getPosition().y - 100));
}

void Boss::Draw(sf::RenderTarget& target)
{
	target.draw(body);

	//target.draw(sss);
	target.draw(this->text);
	//this->sword->Draw(&target);

	//printf("RENDER\n");
}

void Boss::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left
		//this->velocity.x = 0.0f;

		if (this->getPosition().x > this->Pos.x + 250)
		{
			this->canJump = false;
			this->velocity.y = -sqrt(2.0f * 981.0f * this->jumpHeight);
		}
		else
			this->walk = true;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		//this->velocity.x = 0.0f;
		if (this->getPosition().x < this->Pos.x - 250)
		{
			this->canJump = false;
			this->velocity.y = -sqrt(2.0f * 981.0f * this->jumpHeight);
		}
		else
			this->walk = false;
	}

	if (direction.y < 0.0f)
	{
		//Collision on the bottom
		this->velocity.y = 0.0f;
		this->canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		this->velocity.y = 0.0f;
	}
}

float Boss::updateHp(float hit)
{
	this->HP -= hit;
	if (this->HP <= 0)
		this->HP = 0;

	return this->HP;
}

bool Boss::getAttack()
{
	if (animation.currentImage.x == 4)
	{
		if (this->checkAttack)
			return false;
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
	//return 0;
}

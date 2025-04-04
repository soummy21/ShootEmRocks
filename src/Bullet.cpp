#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& direction, float movementSpeed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(position);
	this->movementSpeed = movementSpeed;
	this->direction = direction;

	this->sprite.setScale(0.5f, 0.5f);
}

Bullet::~Bullet()
{
}

void Bullet::tick()
{
	this->sprite.move(this->direction * this->movementSpeed);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

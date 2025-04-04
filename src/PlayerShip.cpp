#include "PlayerShip.h"

void PlayerShip::initVariables()
{
	this->attackCooldownMax = 10.0f;
	this->attackCooldown = this->attackCooldownMax;

	this->movementSpeed = 5.0f;
	this->maxHealth = 20.0f;
	this->health = this->maxHealth;
}

void PlayerShip::initTexture()
{
	//Load a texture from the file system
	if(!this->texture.loadFromFile("Images/spaceship.png"))	
		std::cout << "ERROR::PLAYERSHIP::COULD NOT LOAD TEXTURE" << std::endl;
}

void PlayerShip::initSprite()
{
	//Set the loaded texture onto the sprite
	this->sprite.setTexture(this->texture); 
	this->sprite.setScale(0.12f, 0.12f);
}

PlayerShip::PlayerShip()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::tick()
{
	this->tickAttackCooldown();
}

void PlayerShip::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void PlayerShip::move(const float x, const float y)
{
	//Move the player ship
	sf::Vector2f movement(x, y);
	this->sprite.move(this->movementSpeed * movement);
}

const bool PlayerShip::canAttack()
{
	//Check if the attack cooldown is ready
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		//Reset the attack cooldown
		this->attackCooldown = 0.0f;
		return true;
	}
		
	return false;
}

void PlayerShip::tickAttackCooldown()
{
	//Tick the attack cooldown
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

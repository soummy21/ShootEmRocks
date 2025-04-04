#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <iostream>

class PlayerShip
{
private: 
	sf::Texture texture;
	sf::Sprite sprite;

	//Base Variables
	float movementSpeed;
	int health;
	int maxHealth;

	//Cooldown Variables
	float attackCooldown; //Tracks the time between attacks
	float attackCooldownMax; //The maximum time between attacks

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();

public: 
	PlayerShip();
	virtual ~PlayerShip();

	//Public Methods
	//Lifecycle Methods
	void tick();
	void render(sf::RenderTarget& target);

	void move(const float x, const float y);
	const bool canAttack();

	void tickAttackCooldown();

	//Setters 
	void setPosition(const sf::Vector2f position) { this->sprite.setPosition(position); };
	void setHealth(const int health) { this->health = health; };

	//Getters
	const sf::Vector2f& getPostion() const { return this->sprite.getPosition(); };
	const sf::FloatRect getBounds() const { return this->sprite.getGlobalBounds(); };
	const int& getHealth() const { return this->health; };
	const int& getMaxHealth() const { return this->maxHealth; };
};


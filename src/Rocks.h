#pragma once

#include <SFML\Graphics.hpp>


class Rocks
{
private:
	sf::CircleShape shape;

	unsigned pointCount;
	int type;
	float speed;
	int healthMax;
	int health;
	int damage;
	int points;
	
	void initVariables();
	void initShape();

public: 
	Rocks(sf::Vector2f& pos);
	virtual ~Rocks();

	//Lifecycle Methods
	void tick();
	void render(sf::RenderTarget& target);

	//Getters
	const sf::FloatRect getBounds() const { return this->shape.getGlobalBounds(); }
	const int& getPoints() const { return this->points; }
	const int& getDamage() const { return this->damage; }
};


#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{

private: 
	sf::Sprite sprite;
	sf::Texture* texture;

	sf::Vector2f direction;
	float movementSpeed;

public: 
	Bullet();
	Bullet(sf::Texture* texture, const sf::Vector2f& position, const sf::Vector2f& direction, float movementSpeed);
	virtual ~Bullet();

	//Getters
	const sf::FloatRect getBounds() const { return this->sprite.getGlobalBounds(); };

	//LifeCycle Methods
	void tick();
	void render(sf::RenderTarget& target);
};


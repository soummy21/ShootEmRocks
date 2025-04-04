#include "Rocks.h"

void Rocks::initVariables()
{
	this->pointCount = rand() % 8 + 3; //Randomize the number of points between 3 and 10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount * 0.75f);
	this->healthMax = static_cast<int>(this->pointCount);
	this->health = this->healthMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;

}

void Rocks::initShape()
{	
	//Randomize the radius of the rocks between 20 and 40
	this->shape.setRadius(this->pointCount * 3);
	//Randomize the number of points between 3 and 20
	this->shape.setPointCount(this->pointCount);
	//Randomize the color between 1 and 255 on red green and blue
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Rocks::Rocks(sf::Vector2f & position)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(position);
}

Rocks::~Rocks()
{
}

void Rocks::tick()
{
	this->shape.move(0.0f, speed);
}

void Rocks::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

#pragma once

#include<map>
#include<string>
#include<sstream>

#include "PlayerShip.h"
#include "Bullet.h"
#include "Rocks.h"

class Game
{
private: 
	sf ::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;

	//Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//GUI
	sf::Font font;
	sf::Text pointsText;
	sf::Text gameOverText;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBack;

	//Game Object References
	PlayerShip* playerShip;
	std::vector<Bullet*> bullets;
	std::vector<Rocks*> rocks;

	//Spanwing 
	float spawnTimerValue;
	float spawnTimerMax;

	//Points
	unsigned points;


	//Private Init Methods
	void initGameObjects();
	void initGUI();
	void initTextures();
	void initWindow();

public: 
	Game(); 
	virtual ~Game();

	//Public Lifecycle Methods
	void run();
	void tick();
	void render();
	void renderGUI();

	//Input Methods
	void pollEvents();
	void handleInput();

	//Game Objects Handling
	void tickBullets();
	void tickRocks();

	//Collision
	void limitPlayerToScreen();

	//GUI Methods
	void updateGUI();

};


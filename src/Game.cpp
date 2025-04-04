#include "Game.h"

void Game::initGameObjects()
{
	//Create the player ship
	this->playerShip = new PlayerShip(); 

	//Set the spawn position of the player
	sf::Vector2f spawnPostion = sf::Vector2f(this->window->getSize().x / 2.0f - this->playerShip->getBounds().width / 2.0f, this->window->getSize().y - 50.0f);
	this->playerShip->setPosition(spawnPostion);

	//Set the spawn timer
	this->spawnTimerMax = 50.0f;
	this->spawnTimerValue = this->spawnTimerMax;

	this->points = 10;
}

void Game::initGUI()
{
	//Load font 
	if(!this->font.loadFromFile("Fonts/BAUHS93.ttf"))
		std::cout << "ERROR::GAME::COULD NOT LOAD FONT" << std::endl;
	
	//Initialise point text
	this->pointsText.setFont(this->font);
	this->pointsText.setCharacterSize(20);
	this->pointsText.setFillColor(sf::Color::White);
	this->pointsText.setString("Points: 0");
	this->pointsText.setPosition(650.f, 25.f);
	
	//Initialise game over text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over.");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getLocalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getLocalBounds().height / 2.f
	);

	//Initialise health bar
	this->healthBar.setSize(sf::Vector2f(100.0f, 25.0f));
	this->healthBar.setFillColor(sf::Color::Red);
	this->healthBar.setPosition(sf::Vector2f(20.f, 20.f));

	//Initialise health bar back
	this->healthBarBack = this->healthBar;
	this->healthBarBack.setFillColor(sf::Color(25, 25, 25, 200));


}

void Game::initTextures()
{
	this->textures["Identifier_Bullet"] = new sf::Texture();
	this->textures["Identifier_Bullet"]->loadFromFile("Images/bullet.png");

	if (!this->backgroundTexture.loadFromFile("Images/background.jpg"))
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << std::endl;

	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->backgroundSprite.setScale(0.4f, 0.4f);

}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(
		sf::VideoMode(800, 600), 
		"Shoot Em Rocks", 
		sf::Style::Close | sf::Style::Titlebar
	);

	//Lock the framerate
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initGameObjects();

}

Game::~Game()
{
	delete this->window;
	delete this->playerShip;

	//Delete all the textures in the map
	for (auto& x : this->textures)
	{
		delete x.second;
	}

	//Delete all the bullets in the vector
	for(auto& x : this->bullets)
	{
		delete x;
	}

	//Delete all the rocks in the vector
	for (auto& x : this->rocks)
	{
		delete x;
	}
}

void Game::run()
{
	//Till the time the window is open we run the tick and render per frame 
	while(this->window->isOpen())
	{
		this->pollEvents();

		//Run the game only if the player is alive
		if (this->playerShip->getHealth() > 0)
			this->tick();

		this->render();
	}
}

void Game::tick()
{	
	this->handleInput();
	this->playerShip->tick();
	this->limitPlayerToScreen();

	this->tickBullets();
	this->tickRocks();

	this->updateGUI();
}

void Game::render()
{
	//Clear any previous frame render
	this->window->clear();

	//Draw the background
	this->window->draw(this->backgroundSprite);

	//Draw all the game related stuff
	if(this->window != nullptr)
		this->playerShip->render(*this->window);

	//Draw all the bullets
	for (auto& bullet : this->bullets)
	{
		bullet->render(*this->window);
	}

	//Draw all the rocks
	for (auto& rock : this->rocks)
	{
		rock->render(*this->window);
	}

	renderGUI();
		
	this->window->display();


}

void Game::renderGUI()
{
	//Draw the GUI
	this->window->draw(this->pointsText);
	this->window->draw(this->healthBarBack);
	this->window->draw(this->healthBar);

	if(this->playerShip->getHealth() <= 0)
		this->window->draw(this->gameOverText);

}

void Game::pollEvents()
{
	sf::Event e;
	//Check for events
	while (this->window->pollEvent(e))
	{
		//Check for close button event and close the window
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		//Check for escape key button press and close the window
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();

	}
}

void Game::handleInput()
{
	//On Keyboard pressed A or Left move to the left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->playerShip->move(-1.0f, 0);

	//On Keyboard pressed D or Right move to the right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->playerShip->move(1.0f, 0);

	//On Keyboard pressed W or Up move up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) )
		this->playerShip->move(0, -1.0f);

	//On Keyboard pressed S or Down move down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->playerShip->move(0, 1.0f);

	//On Keyboard pressed Space and the player ship can attack spawn and fire a bullet
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && playerShip->canAttack())
	{
		//Calculate the spawn position of the bullet based on the player ship center and position
		sf::Vector2f spawnPosition = sf::Vector2f(
			this->playerShip->getPostion().x + this->playerShip->getBounds().width / 2.0f,
			this->playerShip->getPostion().y
		);

		//Create bullet that points up and add it to the vector
		this->bullets.push_back(new Bullet(
			this->textures["Identifier_Bullet"],
			spawnPosition,
			sf::Vector2f(0.0f, -1.0f),
			5.0f
		));
	}
}

void Game::tickBullets()
{
	unsigned count = 0;
	for (auto& bullet : this->bullets)
	{
		bullet->tick();

		//Check for bullet culling on the top of the screen and remove it if it is
		if (bullet->getBounds().top + bullet->getBounds().height < 0.0f)
		{
			//Delete the bullet from the heap
			delete this->bullets.at(count);

			//Remove the bullet pointer from the heap 
			this->bullets.erase(this->bullets.begin() + count);
			count--;
		}
			
		count++;

	}
}

void Game::tickRocks()
{
	this->spawnTimerValue += 0.5f;
	if (this->spawnTimerValue >= spawnTimerMax)
	{
		//Reset SpawnTimer 
		this->spawnTimerValue = 0.0f;

		//Spawn a new rock
		sf::Vector2f pos = sf::Vector2f(rand() % this->window->getSize().x - 20.0f, -100.0f);
		this->rocks.push_back(new Rocks(pos));
	}

	//Loop through the rocks and run the tick for each of them 
	for (int i = 0; i < this->rocks.size(); i++)
	{
		bool hasBeenHit = false;

		this->rocks[i]->tick();

		//Check if the rock got hit by the bullet
		for(size_t j = 0; j < this->bullets.size() && !hasBeenHit; j++)
		{
			if(this->bullets[j]->getBounds().intersects(this->rocks[i]->getBounds()))
			{
				this->points += this->rocks[i]->getPoints();

				//Remove the bullet and the rock
				this->bullets.erase(this->bullets.begin() + j);
				this->rocks.erase(this->rocks.begin() + i);
				hasBeenHit = true;
			}
		}

		//Delete rock if it reaches the bottom of the screen and has not been hit
		if (!hasBeenHit)
		{
			if (this->rocks[i]->getBounds().top > this->window->getSize().y)
			{
				delete this->rocks[i];
				this->rocks.erase(this->rocks.begin() + i);
			}
			//Or if the player ship collides with the rock delete the rock
			else if (this->rocks[i]->getBounds().intersects(this->playerShip->getBounds()))
			{
				int rockDamage = this->rocks[i]->getDamage();

				delete this->rocks[i];
				this->rocks.erase(this->rocks.begin() + i);


				//Decrease the health of the player ship
				this->playerShip->setHealth(this->playerShip->getHealth() - rockDamage);
			}
		}
	}
}

void Game::limitPlayerToScreen()
{
	//Check if the player ship has gone out of bounds on the left and reset it
	if(this->playerShip->getBounds().left < 0.0f)
		this->playerShip->setPosition(sf::Vector2f(0.0f, this->playerShip->getBounds().top));
	//Check if the player ship has gone out of bounds on the right and reset it
	else if (this->playerShip->getBounds().left + this->playerShip->getBounds().width > this->window->getSize().x)
			this->playerShip->setPosition(sf::Vector2f(this->window->getSize().x - this->playerShip->getBounds().width, this->playerShip->getBounds().top));

	//Check if the player ship has gone out of bounds on the top and reset it
	if(this->playerShip->getBounds().top < 0.0f)
		this->playerShip->setPosition(sf::Vector2f(this->playerShip->getBounds().left, 0.0f));
	//Check if the player ship has gone out of bounds on the bottom and reset it
	else if (this->playerShip->getBounds().top + this->playerShip->getBounds().height > this->window->getSize().y)
		this->playerShip->setPosition(sf::Vector2f(this->playerShip->getBounds().left, this->window->getSize().y - this->playerShip->getBounds().height));


}

void Game::updateGUI()
{
	//Update Points Text
	std::stringstream ss;
	ss<<"Points: "<<this->points;
	this->pointsText.setString(ss.str());

	//Calculate the health percentage and set the health bar size based on it
	float healthPercentage = (static_cast<float>(this->playerShip->getHealth()) / this->playerShip->getMaxHealth());

	//Clamp it to a minimum of 0%
	if(healthPercentage< 0.0f) 
		healthPercentage = 0.0f;


	this->healthBar.setSize(sf::Vector2f(this->healthBarBack.getSize().x * healthPercentage, this->healthBarBack.getSize().y));
}

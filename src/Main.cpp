// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Game.h"

#include<cstdlib>
#include<ctime>

int main()
{
	//Set the random seed
	srand(std::time(0));

	//Create the game and run
	Game game; 
	game.run();

	return 0;
}


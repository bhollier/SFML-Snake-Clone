//Standard C++:
#include <iostream>
//Standard C:
#include <cstdlib>
#include <time.h>
//SFML Headers:
#include <SFML/Graphics.hpp>
//My Headers:
#include "Game.hpp"

int main()
{
    srand(time(NULL));
    //Create a game object:
    Game game;
    //Initiate the game loop:
    game.gameLoop();
    //Quit safely:
    return 0;
}


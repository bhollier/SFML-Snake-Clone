#ifndef GAME_HPP
#define GAME_HPP

//Standard C++:
#include <stack>
//SFML Headers:
#include <SFML/Graphics.hpp>
//My Headers:
#include "FPS.hpp"
#include "Snake.hpp"

class Game
{
    public:
        //WINDOW====================================
        sf::RenderWindow window;
        bool windowInFocus = true;

        //RESOURCES=================================
        //Load Game Assets:
        void loadAssets();

        //GAME OBJECTS==============================
        FPS gameFPS;
        Snake snake;

        //GAME LOOP=================================
        void handleInput();
        void gameLoop();

        //Constructor:
        Game();
};

#endif // GAME_HPP

//Standard C++:
#include <stack>
#include <iostream>
#include <fstream>
#include <dirent.h>
//SFML Headers:
#include <SFML/Graphics.hpp>
//My Headers:
#include "Game.hpp"

//Load Game Assets:
void Game::loadAssets()
{
    sf::Font temp;
    temp.loadFromFile("Impact.ttf");
    gameFPS.setFont(temp);
    gameFPS.setColour(sf::Color::Black);
    gameFPS.setCharacterSize(16);
    gameFPS.setPosition(sf::Vector2f(10, 10));
}

//The game loop:
void Game::handleInput()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {window.close();}
        else if (event.type == sf::Event::GainedFocus) {windowInFocus = true;}
        else if (event.type == sf::Event::LostFocus) {windowInFocus = false;}
        else if (event.type == sf::Event::KeyPressed)
        {
            if (windowInFocus)
            {
                if (event.key.code == sf::Keyboard::Escape) {window.close();}
            }
        }
    }

    if (windowInFocus)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
        {
            snake.changeDirection(up);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
        {
            snake.changeDirection(down);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
        {
            snake.changeDirection(left);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        {
            snake.changeDirection(right);
        }
    }
}
void Game::gameLoop()
{
    //While the window is open:
    while (window.isOpen())
    {
        //Handle input:
        handleInput();
        //Update Snake:
        snake.update();
        //Clear the screen before drawing:
        window.clear(sf::Color::White);
        //Draw snake:
        snake.draw(window);
        gameFPS.draw(window);
        //Display everything that was drawn:
        window.display();
    }
}

//Constructor:
Game::Game()
{
    //Create a window:
    window.create(sf::VideoMode(400, 400), "Snake");
    //Set the framerate limit to 60 fps:
    window.setFramerateLimit(60);

    loadAssets();
}

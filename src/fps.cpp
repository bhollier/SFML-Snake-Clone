//Standard C++:
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
//SFML Headers:
#include <SFML/Graphics.hpp>
//My Headers:
#include "FPS.hpp"

void FPS::setFont(const sf::Font& newFont)
{
    fpsDisplayFont = newFont;
    fpsDisplayText.setFont(fpsDisplayFont);
}
void FPS::setCharacterSize(const int& newSize)
{
    fpsDisplayText.setCharacterSize(newSize);
}
void FPS::setColour(const sf::Color& newColour)
{
    fpsDisplayText.setColor(newColour);
}
void FPS::setPosition(const sf::Vector2f& newPosition)
{
    fpsDisplayText.setPosition(newPosition);
}

void FPS::draw(sf::RenderWindow& targetWindow)
{
    sf::Time timeElapsed = fpsClock.getElapsedTime();

    if (timeElapsed.asMicroseconds() >= 500000) //If it's been half a second
    {
        std::stringstream temp;
        temp << frameCounter * 2;
        std::string fpsCounterStr = temp.str();

        fpsDisplayText.setString(fpsCounterStr);
        //Reset variables:
        frameCounter = 0;
        fpsClock.restart();
    }

    targetWindow.draw(fpsDisplayText);
    ++frameCounter;
}

FPS::FPS()
{
    fpsDisplayText.setPosition(sf::Vector2f(4, 4));
}

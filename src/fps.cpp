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
    //Copy the font:
    fpsDisplayFont = newFont;
    //Set the text to the copy:
    fpsDisplayText.setFont(fpsDisplayFont);
}
void FPS::setCharacterSize(const int& newSize)
{
    //Set the new character size
    fpsDisplayText.setCharacterSize(newSize);
}
void FPS::setColour(const sf::Color& newColour)
{
    //Set the new colour
    fpsDisplayText.setColor(newColour);
}
void FPS::setPosition(const sf::Vector2f& newPosition)
{
    //Set the new position
    fpsDisplayText.setPosition(newPosition);
}

void FPS::draw(sf::RenderWindow& targetWindow)
{
    //Get the elapsed time of the clock:
    sf::Time timeElapsed = fpsClock.getElapsedTime();
    
    if (timeElapsed.asMicroseconds() >= 500000) //If it's been half a second
    {
        //Stringstream to convert frameCounter to a string
        std::stringstream temp;
        //Put the frame counter into the stringstream but doubled (because it run every half second):
        temp << frameCounter * 2;
        //Set the new string from the stringstream
        std::string fpsCounterStr = temp.str();

        //Set the drawable text object to the newly created string
        fpsDisplayText.setString(fpsCounterStr);
        //Reset variables:
        frameCounter = 0;
        fpsClock.restart();
    }

    //Draw the text object:
    targetWindow.draw(fpsDisplayText);
    //Increase the framerate counter
    ++frameCounter;
}

FPS::FPS()
{
    //Set the text so it doesn't overlap the border:
    fpsDisplayText.setPosition(sf::Vector2f(4, 4));
}

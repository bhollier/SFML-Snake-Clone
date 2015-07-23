#ifndef FPS_HPP
#define FPS_HPP

//Standard C++:
#include <string>
#include <sstream>
//SFML Headers:
#include <SFML/Graphics.hpp>
//My Headers:
#include "Time.hpp"

class FPS
{
    private:
        sf::Clock fpsClock;
        int frameCounter;
        sf::Font fpsDisplayFont;
        sf::Text fpsDisplayText;

    public:
        void setFont(const sf::Font& newFont);
        void setCharacterSize(const int& newSize);
        void setColour(const sf::Color& newColour);
        void setPosition(const sf::Vector2f& newPosition);

        void draw(sf::RenderWindow& targetWindow);

        //Constructor:
        FPS();
};

#endif // FPS_HPP

#ifndef SNAKE_HPP
#define SNAKE_HPP

//Standard C++:
#include <array>
#include <vector>
//SFML Headers:
#include <SFML/Graphics.hpp>
//Multi threading:
#include <omp.h>

enum direction {up, down, right, left, none};

class Snake
{
    private:
        std::array<std::array<int, 40>, 40> board;
        direction snakeDirection;
        sf::Vector2f appleLocation;

        //bool appleOnBoard = false;
        sf::Clock snakeMoveClock;
        std::vector<sf::Vector2f> snakeBodyPartLocations;

    public:
        void changeDirection(direction newSnakeDirection)
        {
            if (((snakeDirection == up)   && (newSnakeDirection != down))  || ((snakeDirection == down) && (newSnakeDirection != up)) ||
                ((snakeDirection == left) && (newSnakeDirection != right)) || ((snakeDirection == right) && (newSnakeDirection != left)))
            {
                snakeDirection = newSnakeDirection;
            }
            else if (snakeBodyPartLocations.size() == 1)
            {
                snakeDirection = newSnakeDirection;
            }
        }

        void update()
        {
            sf::Time elapsedTime = snakeMoveClock.getElapsedTime();
            if (elapsedTime.asMilliseconds() >= 150)
            {
                for (int i = signed(snakeBodyPartLocations.size() - 1); i >= 0; --i)
                {
                    if (i == 0)
                    {
                        sf::Vector2f snakeHeadLocation = snakeBodyPartLocations.at(0);
                        if (snakeDirection == up) {snakeHeadLocation.y = snakeHeadLocation.y - 1;}
                        else if (snakeDirection == right) {snakeHeadLocation.x = snakeHeadLocation.x + 1;}
                        else if (snakeDirection == down) {snakeHeadLocation.y = snakeHeadLocation.y + 1;}
                        else if (snakeDirection == left) {snakeHeadLocation.x = snakeHeadLocation.x - 1;}

                        snakeBodyPartLocations.at(0) = snakeHeadLocation;

                    }
                    else if (i == signed(snakeBodyPartLocations.size() - 1))
                    {
                        snakeBodyPartLocations.at(i) = snakeBodyPartLocations.at(i - 1);
                    }
                    else
                    {
                        snakeBodyPartLocations.at(i) = snakeBodyPartLocations.at(i - 1);
                    }
                }

                if ((appleLocation.x == snakeBodyPartLocations.at(0).x) && (appleLocation.y == snakeBodyPartLocations.at(0).y))
                {
                    while (true)
                    {
                        int randomAppleX = rand() % 38 + 1;
                        int randomAppleY = rand() % 38 + 1;
                        if (board.at(randomAppleY).at(randomAppleX) == 0)
                        {
                            board.at(randomAppleY).at(randomAppleX) = 2;
                            appleLocation = sf::Vector2f(randomAppleX, randomAppleY);
                            break;
                        }
                    }

                    if (snakeBodyPartLocations.size() == 1)
                    {
                        sf::Vector2f tailLocation = snakeBodyPartLocations.back();
                        if (snakeDirection == up) {tailLocation.y = tailLocation.y + 1;}
                        else if (snakeDirection == down) {tailLocation.y = tailLocation.y - 1;}
                        else if (snakeDirection == right) {tailLocation.x = tailLocation.x + 1;}
                        else if (snakeDirection == left) {tailLocation.x = tailLocation.x - 1;}
                        snakeBodyPartLocations.push_back(tailLocation);
                    }
                    else
                    {
                        sf::Vector2f tailLocation = snakeBodyPartLocations.back();
                        if (snakeBodyPartLocations.at(snakeBodyPartLocations.size() - 2).x == tailLocation.x + 1) {tailLocation.x = tailLocation.x - 1;}
                        else if (snakeBodyPartLocations.at(snakeBodyPartLocations.size() - 2).x == tailLocation.x - 1) {tailLocation.x = tailLocation.x + 1;}
                        else if (snakeBodyPartLocations.at(snakeBodyPartLocations.size() - 2).y == tailLocation.y + 1) {tailLocation.y = tailLocation.y - 1;}
                        else if (snakeBodyPartLocations.at(snakeBodyPartLocations.size() - 2).y == tailLocation.y - 1) {tailLocation.y = tailLocation.y + 1;}
                        snakeBodyPartLocations.push_back(tailLocation);
                    }
                }

                for (int i = 0; i < signed(snakeBodyPartLocations.size()); ++i)
                {
                    if ((snakeBodyPartLocations.at(i).x < 1) || (snakeBodyPartLocations.at(i).x > 38) ||
                        (snakeBodyPartLocations.at(i).y < 1) || (snakeBodyPartLocations.at(i).y > 38))
                    {
                        reset();
                    }

                    if ((i != 0) && (snakeBodyPartLocations.at(0).x == snakeBodyPartLocations.at(i).x) &&
                        (snakeBodyPartLocations.at(0).y == snakeBodyPartLocations.at(i).y))
                    {
                        reset();
                    }
                }

                for (int y = 0; y < signed(board.size()); y++) {for (int x = 0; x < signed(board.at(0).size()); ++x)
                {
                    if ((y == 0) || (y == 39) || (x == 0) || (x == 39)) {board.at(y).at(x) = 3;}
                    else {board.at(y).at(x) = 0;}
                }}
                for (int i = 0; i < signed(snakeBodyPartLocations.size()); ++i)
                {
                    board.at(snakeBodyPartLocations.at(i).y).at(snakeBodyPartLocations.at(i).x) = 1;
                }
                board.at(appleLocation.y).at(appleLocation.x) = 2;

                snakeMoveClock.restart();
            }
        }

        void draw(sf::RenderWindow& targetWindow)
        {
            for (int y = 0; y < signed(board.size()); y++) {for (int x = 0; x < signed(board.at(0).size()); ++x)
            {
                if ((board.at(y).at(x) == 1) || (board.at(y).at(x) == 2) || (board.at(y).at(x) == 3))
                {
                    sf::RectangleShape block;
                    block.setSize(sf::Vector2f(10, 10));
                    block.setPosition(x * 10, y * 10);

                    if (board.at(y).at(x) == 1) {block.setFillColor(sf::Color::Green);}
                    else if (board.at(y).at(x) == 2) {block.setFillColor(sf::Color::Red);}
                    else if (board.at(y).at(x) == 3) {block.setFillColor(sf::Color::Black);}

                    targetWindow.draw(block);
                }
            }}
        }

        void reset()
        {
            //Generate an apple:
            while (true)
            {
                int randomAppleX = rand() % 38 + 1;
                int randomAppleY = rand() % 38 + 1;
                if (board.at(randomAppleY).at(randomAppleX) == 0)
                {
                    board.at(randomAppleY).at(randomAppleX) = 2;
                    appleLocation = sf::Vector2f(randomAppleX, randomAppleY);
                    break;
                }
            }

            //Put the snake on the board:
            snakeBodyPartLocations.clear();
            snakeBodyPartLocations.push_back(sf::Vector2f(20, 20));
            snakeDirection = down;
        }

        Snake()
        {
            reset();
        }
};

#endif // SNAKE_HPP

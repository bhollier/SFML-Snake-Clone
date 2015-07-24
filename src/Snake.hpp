#ifndef SNAKE_HPP
#define SNAKE_HPP

//Standard C++:
#include <array>
#include <vector>
//SFML Headers:
#include <SFML/Graphics.hpp>

//Enumerator for all four directions:
enum direction {up, down, right, left, none};

class Snake
{
    private:
        //2D Array for displaying board:
        std::array<std::array<int, 40>, 40> board;
        //Direction the snake is moving:
        direction snakeDirection;
        //Location of apple:
        sf::Vector2f appleLocation;

        //So the snake doesn't move slower/faster depending on the framerate:
        sf::Clock snakeMoveClock;
        //Vector of each pixel of snake body parts:
        std::vector<sf::Vector2f> snakeBodyPartLocations;

    public:
        //Function so the player can change it's direction:
        void changeDirection(direction newSnakeDirection)
        {
            //If statement so the user doesn't kill themself by moving backwards:
            if (((snakeDirection == up)   && (newSnakeDirection != down))  || ((snakeDirection == down) && (newSnakeDirection != up)) ||
                ((snakeDirection == left) && (newSnakeDirection != right)) || ((snakeDirection == right) && (newSnakeDirection != left)))
            {
                snakeDirection = newSnakeDirection;
            }
            //Unless the snake is only one pixel:
            else if (snakeBodyPartLocations.size() == 1)
            {
                snakeDirection = newSnakeDirection;
            }
        }

        void update()
        {
            sf::Time elapsedTime = snakeMoveClock.getElapsedTime();
            //Update every 150ms:
            if (elapsedTime.asMilliseconds() >= 150)
            {
                //Go through every body part and move:
                for (int i = signed(snakeBodyPartLocations.size() - 1); i >= 0; --i)
                {
                    //If it's the snake's head:
                    if (i == 0)
                    {
                        sf::Vector2f snakeHeadLocation = snakeBodyPartLocations.at(0);
                        if (snakeDirection == up) {snakeHeadLocation.y = snakeHeadLocation.y - 1;}
                        else if (snakeDirection == right) {snakeHeadLocation.x = snakeHeadLocation.x + 1;}
                        else if (snakeDirection == down) {snakeHeadLocation.y = snakeHeadLocation.y + 1;}
                        else if (snakeDirection == left) {snakeHeadLocation.x = snakeHeadLocation.x - 1;}

                        snakeBodyPartLocations.at(0) = snakeHeadLocation;

                    }
                    //Else:
                    else
                    {
                        snakeBodyPartLocations.at(i) = snakeBodyPartLocations.at(i - 1);
                    }
                }

                //If the snake's head hit the apple:
                if ((appleLocation.x == snakeBodyPartLocations.at(0).x) && (appleLocation.y == snakeBodyPartLocations.at(0).y))
                {
                    //Generate a new apple:
                    while (true) //While statement untill a apple isn't inside the snake's body
                    {
                        int randomAppleX = rand() % 38 + 1;
                        int randomAppleY = rand() % 38 + 1;
                        if (board.at(randomAppleY).at(randomAppleX) == 0)
                        {
                            board.at(randomAppleY).at(randomAppleX) = 2;
                            appleLocation = sf::Vector2f(randomAppleX, randomAppleY);
                            break; //Break because it isn't in the snake's body
                        }
                    }

                    //Grow the Snake:
                    //If the snake is one pixel, create a new body part
                    //in the direction opposite to where it's moving:
                    if (snakeBodyPartLocations.size() == 1)
                    {
                        sf::Vector2f tailLocation = snakeBodyPartLocations.back();
                        if (snakeDirection == up) {tailLocation.y = tailLocation.y + 1;}
                        else if (snakeDirection == down) {tailLocation.y = tailLocation.y - 1;}
                        else if (snakeDirection == right) {tailLocation.x = tailLocation.x + 1;}
                        else if (snakeDirection == left) {tailLocation.x = tailLocation.x - 1;}
                        snakeBodyPartLocations.push_back(tailLocation);
                    }
                    //If the snake is larger than one pixel, create a body part
                    //that follows the pattern the snake is moving in:
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

                //Check if the snake has collided with something:
                for (int i = signed(snakeBodyPartLocations.size() - 1); i >= 0; --i)
                {
                    //If any of the body parts collide with the border:
                    if ((snakeBodyPartLocations.at(i).x < 1) || (snakeBodyPartLocations.at(i).x > 38) ||
                        (snakeBodyPartLocations.at(i).y < 1) || (snakeBodyPartLocations.at(i).y > 38))
                    {
                        reset(); //Reset the grid
                    }

                    //If any of the body parts collide with the snake's head:
                    if ((i != 0) && (snakeBodyPartLocations.at(0).x == snakeBodyPartLocations.at(i).x) &&
                        (snakeBodyPartLocations.at(0).y == snakeBodyPartLocations.at(i).y))
                    {
                        reset(); //Reset the grid
                    }
                }

                //Update the board:
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

                //Restart the clock
                snakeMoveClock.restart();
            }
        }

        void draw(sf::RenderWindow& targetWindow)
        {
            //Go through the board:
            for (int y = 0; y < signed(board.size()); y++) {for (int x = 0; x < signed(board.at(0).size()); ++x)
            {
                //If it's a drawable type:
                if ((board.at(y).at(x) == 1) || (board.at(y).at(x) == 2) || (board.at(y).at(x) == 3))
                {
                    //Create a rectangle:
                    sf::RectangleShape block;
                    block.setSize(sf::Vector2f(10, 10));
                    block.setPosition(x * 10, y * 10);

                    //Colour the rectangle accordingly:
                    if (board.at(y).at(x) == 1) {block.setFillColor(sf::Color::Green);}
                    else if (board.at(y).at(x) == 2) {block.setFillColor(sf::Color::Red);}
                    else if (board.at(y).at(x) == 3) {block.setFillColor(sf::Color::Black);}

                    //Draw the rectangle
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
            //Reset the game:
            reset();
        }
};

#endif // SNAKE_HPP

#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
    std::vector<Brick> getBricks();
    void shake();

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;
    int brickCounter = 0;
    static constexpr float TOP_PADDING = 100.0f;
};

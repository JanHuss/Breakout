#include "BrickManager.h"


BrickManager::BrickManager(sf::RenderWindow* window)
    : _window(window)
{
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);
    brickCounter = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight);
            // set brick colour and lifes
            if (i == 0 && brickCounter < _bricks.size())
            {
                _bricks[brickCounter].brickColour = RED;
                _bricks[brickCounter].setBrickColour();
                brickCounter++;
            }
            if (i == 1 || i == 2 && brickCounter < _bricks.size())
            {
                _bricks[brickCounter].brickColour = AMBER;
                _bricks[brickCounter].setBrickColour();
                brickCounter++;
            }
            else if (i == 3 || i == 4 && brickCounter < _bricks.size())
            {
                _bricks[brickCounter].brickColour = GREEN;
                _bricks[brickCounter].setBrickColour();
                brickCounter++;
            }
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) 
    {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
	
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        
        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // red brick
        if (brick.brickColour == RED)
        {
            brick.brickColour = AMBER;
            brick.setBrickColour(); 
            break;
        }
        if (brick.brickColour == AMBER)
        {
            brick.brickColour = GREEN;
            brick.setBrickColour(); 
            break;
        }
        if (brick.brickColour == GREEN)
        {
            // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
            // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
            brick = _bricks.back();
            _bricks.pop_back();
            break;
        }        
    }
    return collisionResponse;
}

std::vector<Brick> BrickManager::getBricks()
{
    return _bricks;
}

void BrickManager::shake()
{
    for (auto& brick: _bricks)
    {
        // move them randomly 
        brick.getShape().move(rand()% 30, rand()% 50);
    }
    for (auto& brick : _bricks)
    {
        // set back to original position
    }
}

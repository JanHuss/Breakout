#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Paddle
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();

    void update(float dt);
    void handleInput(float dt);
    void setPosition(float x);
	sf::Vector2f getPosition();
	float getWidth() const;
    void paddleReset();
    void render();
    void moveLeft(float dt);
    void moveRight(float dt);
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

    void setSmallPaddle(float duration);
    void setBigPaddle(float duration);
    void setReversePaddle(float duration);
    void setInvisiblePaddle(float duration);

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    float _widthDiff;
    float _timeWithPowerupEffect;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
    float speed = 50.0f;

    bool _isSmallPaddle;
    bool _isBigPaddle;
    bool _isReversePaddle;
    bool _isInvisiblePaddle;
};

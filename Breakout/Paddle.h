#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Paddle
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void update(float dt);
    void setPosition(float x);
	sf::Vector2f getPosition();
	float getWidth() const;
    void paddleReset();
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
    float speed = 50.0f;
};

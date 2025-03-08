#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
}

void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }

    if (_width < _sprite.getSize().x)
            _sprite.setSize(sf::Vector2f( _sprite.getSize().x - speed * dt, _sprite.getSize().y));
    if (_width > _sprite.getSize().x)
            _sprite.setSize(sf::Vector2f( _sprite.getSize().x + speed * dt, _sprite.getSize().y));

    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);

    _sprite.getPosition();

}

void Paddle::setPosition(float x)
{
	_sprite.setPosition(x - _width/2, _sprite.getPosition().y);
}

sf::Vector2f Paddle::getPosition()
{
	return _sprite.getPosition();
}

float Paddle::getWidth() const
{
    return _width;
}

void Paddle::paddleReset()
{
	_sprite.setPosition((_window->getSize().x - _width) / 2.0f, _window->getSize().y - 50.0f);
	_isAlive = true;
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    // if the width is less than the sprite's get size.x
    //if (_width < _sprite.getSize().x)
    //{   
    //// for as long as the width is less than the getsize.x
    //    while(_width < _sprite.getSize().x)
    //         // decrease the sprite's get size.x by 0.1f
    //        _sprite.setSize(sf::Vector2f( _sprite.getSize().x - 0.1f, _sprite.getSize().y));
    //
    //}
    _timeInNewSize = duration;
    //float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    //_sprite.setPosition(newX, _sprite.getPosition().y);
}

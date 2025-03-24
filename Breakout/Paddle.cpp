#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true),  
    _timeWithPowerupEffect(0.f)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
    _sprite.setPosition(_window->getSize().x/2 - _sprite.getSize().x / 2, _window->getSize().y - 50.0f);

    // set Mouse to centre of window
	sf::Vector2u windowSize = _window->getSize();
	sf::Vector2i centerPosition(windowSize.x / 2, _sprite.getPosition().y + _sprite.getSize().y / 2);
	sf::Mouse::setPosition(centerPosition, *_window);
    
	if (sf::Joystick::isConnected(0))
	{
		// joystick number 0 is connected
			// instead of an output, perhaps display it in the window
		std::cout << "Joystick 0 is connected" << std::endl;
        std::cout << "Joystick button count: " << sf::Joystick::getButtonCount(0) << std::endl;
	}
    else
        std::cout << "Joystick 0 is NOT connected" << std::endl;

}

Paddle::~Paddle()
{
}



void Paddle::update(float dt)
{
	// check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
            // disable powerups
            setBigPaddle(0);    
            setSmallPaddle(0);
            setReversePaddle(0);
            
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.      
    }

    //_window->setMouseCursorVisible(false);
    if (_isSmallPaddle || _isBigPaddle || _isReversePaddle)
        _sprite.setFillColor(sf::Color(paddleEffectsColour));

    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }

    if (_width < _sprite.getSize().x)
    {
            _sprite.setSize(sf::Vector2f( _sprite.getSize().x - speed * dt, _sprite.getSize().y));
    }
    if (_width > _sprite.getSize().x)
    {
            _sprite.setSize(sf::Vector2f( _sprite.getSize().x + speed * dt, _sprite.getSize().y));
    }
    // this allows the mouse to move but prevents the keyboard input from moving
    // currently sets itself to right on initialisation
    // these two lines are not needed if the game does not require mouse controls
    //float newX = sf::Mouse::getPosition().x - (_sprite.getSize().x / 2);
    //_sprite.setPosition(newX, _sprite.getPosition().y);

    if (_width == PADDLE_WIDTH)
        _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
    //_sprite.getPosition();

    
    handleInput(dt);

}

void Paddle::handleInput(float dt)
{
    // stop paddle going off screen
	if (_sprite.getPosition().x < 0) 
		_sprite.setPosition(0.5f, _sprite.getPosition().y);
	if (_sprite.getPosition().x + _sprite.getSize().x > _window->getSize().x) 
		_sprite.setPosition(_window->getSize().x - _sprite.getSize().x - 0.5f, _sprite.getPosition().y);

    // --- Keyboard Controls ---
	    moveRight(dt);
	    moveLeft(dt);
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
    //sf::Mouse::setPosition(_window->getPosition()/2);
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

void Paddle::moveLeft(float dt)
{
	float position = _sprite.getPosition().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) == -100 ||
		sf::Joystick::isButtonPressed(0, 4) &&
		position > 0)
	{
		if (!_isReversePaddle)
			_sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
		else
			_sprite.move(sf::Vector2f(-dt * -PADDLE_SPEED, 0));
	}
}

void Paddle::moveRight(float dt)
{
	float position = _sprite.getPosition().x;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) == 100 ||
		sf::Joystick::isButtonPressed(0, 5) &&
		position < _window->getSize().x - _width)
	{
		if (!_isReversePaddle)
			_sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
		else
			_sprite.move(sf::Vector2f(dt * -PADDLE_SPEED, 0));
	}
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _widthDiff = abs(PADDLE_WIDTH - _width);
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

void Paddle::setSmallPaddle(float duration)
{
    if (duration)
	{
		_isSmallPaddle = true;
		_timeWithPowerupEffect = duration;
		return;
	}
	_isSmallPaddle = false;
	_timeWithPowerupEffect = 0.f;
}

void Paddle::setBigPaddle(float duration)
{
    if (duration)
	{
		_isBigPaddle = true;
		_timeWithPowerupEffect = duration;
		return;
	}
	_isBigPaddle = false;
	_timeWithPowerupEffect = 0.f;
}

void Paddle::setReversePaddle(float duration)
{
    if (duration)
	{
		_isReversePaddle = true;
		_timeWithPowerupEffect = duration;
		return;
	}
	_isReversePaddle = false;
	_timeWithPowerupEffect = 0.f;
}

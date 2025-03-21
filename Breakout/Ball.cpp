#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, Engine* audioEng)
    : _window(window), _velocity(velocity), _gameManager(gameManager), audioEngine(audioEng),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
    
    // Audio - assigning leafs to pointers
    paddle = audioEngine->getEventManagerInstance().paddle;
    brick = audioEngine->getEventManagerInstance().brick;
    bounds = audioEngine->getEventManagerInstance().bounds;
    bounds->setPitch(0.5f);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            // disable powerups
            setFireBall(0);    
            setSlowBall(0);
            setFastBall(0);
            
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }
    // SlowBall Colour change
    if (_isSlowBall || _isFastBall)
         _sprite.setFillColor(sf::Color(ballEffectsColour));

    

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    ballCollisions(dt);
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::ballCollisions(float dt)
{
    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on left walls
    if ((position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
        // play sound here
        //bounds->setPitch((float)(rand() % 1) - 2.0f);
        bounds->setPanning(0.8f, 0.2f);
        bounds->play();
    }
    // bounce on right walls
    else if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0))
    {
        _direction.x *= -1;
        // play sound here
        //bounds->setPitch((float)(rand() % 1) - 2.0f);
        bounds->setPanning(0.2f, 0.8f);
        bounds->play();
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
        // play sound here
        //bounds->setPitch(0.5f);
        //bounds->setPitch((float)(rand() % 1) - 2.0f);
        panToBallPosition();
        bounds->play();
    }

    // hits bottom of window and player loses life
    if (position.y > windowDimensions.y)
    {
        _gameManager->loseLife();
        // lose life sound here
        // place new position of ball
        _sprite.setPosition(0, 300);
        // stop game for 3 seconds so that the player can predict the ball
        // set a random direction downwards
        _direction = { 1, 1 };
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    
        // audio one-shot ball collides with paddle
        paddle->play();
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    //if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        if (!_isFireBall)
            _direction.x *= -1; // Bounce horizontally
        // audio one-shot ball collides with brick
        brick->play();

    }
    else if (collisionResponse == 2)
    {
        if (!_isFireBall)
            _direction.y *= -1; // Bounce vertically
        // audio one-shot ball collides with brick
        brick->play();
    }
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration; 
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::setSlowBall(float duration)
{
    if (duration) 
    {
        _isSlowBall = true;
        _timeWithPowerupEffect = duration; 
        return;
    }
    _isSlowBall = false;
    _timeWithPowerupEffect = 0.f; 
    audioEngine->getEventManagerInstance().gameMusic->setPitch(0.0f);
}

void Ball::setFastBall(float duration)
{
	if (duration)
	{
		_isFastBall = true;
		_timeWithPowerupEffect = duration;
		return;
	}
	_isFastBall = false;
	_timeWithPowerupEffect = 0.f;
	audioEngine->getEventManagerInstance().gameMusic->setPitch(0.0f);
}

void Ball::panToBallPosition()
{  
    // left outer fifth
    if (_sprite.getPosition().x > 0 && 
        _sprite.getPosition().x < _window->getSize().x/5)
        bounds->setPanning(0.8f, 0.2f);
    // left inner fifth
    if (_sprite.getPosition().x > _window->getSize().x/5 && 
        _sprite.getPosition().x < (_window->getSize().x/5)*2)
        bounds->setPanning(0.6f, 0.4f);
    // centre fifth
    if (_sprite.getPosition().x > (_window->getSize().x/5)*2 &&
        _sprite.getPosition().x < _window->getSize().x - (_window->getSize().x/5)*2)
        bounds->setPanning(0.5f, 0.5f);
    // right inner quarter
    if (_sprite.getPosition().x > _window->getSize().x - (_window->getSize().x/5)*2 && 
        _sprite.getPosition().x < _window->getSize().x - _window->getSize().x/5)
        bounds->setPanning(0.4f, 0.6f);
    // right outer quarter
    if (_sprite.getPosition().x >_window->getSize().x - _window->getSize().x/5 &&
        _sprite.getPosition().x < _window->getSize().x)
        bounds->setPanning(0.2f, 0.8f);
}

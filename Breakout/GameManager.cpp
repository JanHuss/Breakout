#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    _levelText.setFont(_font);
    _levelText.setPosition(_window->getSize().x - 200, 20);
    _levelText.setCharacterSize(48);
    _levelText.setFillColor(sf::Color::Yellow);

	level = 5;

    // strings
	gameOverText = "Game over. \nPress Enter to restart game";
	pauseText = "Paused. \nPress Enter to reset game\nPress Esc to exit application";
	levelCompleteText = "Level complete. \nPress Enter to continue";
}

void GameManager::initialize()
{
	// set mouse to centre of window
    sf::Vector2u windowSize = _window->getSize();
    sf::Vector2i centerPosition(windowSize.x / 2, windowSize.y / 2);
	sf::Mouse::setPosition(centerPosition, *_window);

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);

	// set level text
	_levelText.setString("Level: " + std::to_string(level));
}

void GameManager::deleteObjects()
{
	delete _paddle;
	delete _brickManager;
	delete _ball;
	delete _powerupManager;
	delete _ui;
}



void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
    

    if (_lives <= 0)
    {
        _masterText.setString(gameOverText);
		resetGame(gameOverText, 0);
        return;
    }
    if (_levelComplete)
    {
		_masterText.setString(levelCompleteText);
		resetGame(levelCompleteText, 1);
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString(pauseText);
            _pauseHold = PAUSE_TIME_BUFFER;
			// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) _window->close(); // won't work unless I change the pause menu. Delta time stops running when paused.
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle keyboard
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _paddle->moveLeft(dt);

    // stop paddle going off screen
	if (_paddle->getPosition().x < 0) _paddle->setPosition(0.5f);
	if (_paddle->getPosition().x > _window->getSize().x) _paddle->setPosition(_window->getSize().x - 0.5f);

	// mouse input
	_window->setMouseCursorVisible(false);
	sf::Vector2i gloalMousePosition = sf::Mouse::getPosition();
	sf::Vector2i localMousePosition = sf::Mouse::getPosition(*_window);

    // stop paddle going off screen
	if (localMousePosition.x - _paddle->getWidth()/2 < 0) localMousePosition.x = 0.5f + _paddle->getWidth()/2;
	if (localMousePosition.x + _paddle->getWidth()/2 > _window->getSize().x) localMousePosition.x = _window->getSize().x - 0.5f - _paddle->getWidth()/2;

    // move paddle with mouse
    _paddle->setPosition(static_cast<float>(localMousePosition.x)); 
	
    // quit game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) _window->close();

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
	_window->draw(_levelText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::resetGame(std::string message, int levelIncrease)
{
	// game over
    if (_masterText.getString() == gameOverText)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                // reset lives
			    _lives = 3;
			    // reset bricks
                _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
                // reset life images
                _ui->resetLives(_lives);
			    // recentre paddle
				_paddle->paddleReset();
				// remove game over text
                _masterText.setString("");


				// reset level
				level = 0;

				deleteObjects();
				initialize();
            }
	}
    // new level
    else if (_masterText.getString() == levelCompleteText)
    {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                // reset lives
			    _lives = 3;
			    // reset bricks
                _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
                // reset life images
                _ui->resetLives(_lives);
			    // recentre paddle
				_paddle->paddleReset();
				// remove game over text
                _masterText.setString("");
				// increase level
				level += levelIncrease;

				deleteObjects();
				initialize();
            }
    }
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }

#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>


GameManager::GameManager(sf::RenderWindow* window, Engine* audioEng)
    : _window(window), audioEngine(audioEng), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
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

	_level = 0;

    // strings
	gameOverText = "Game over. \nPress Enter to restart game";
	pauseText = "Paused. \nPress Enter to reset game\nPress Esc to exit application";
	levelCompleteText = "Level complete. \nPress Enter to continue";

    // audio engine
    smilyDayMusic = audioEngine->getEventManagerInstance().gameMusic;
    pause = audioEngine->getEventManagerInstance().pause;
    gameOver = audioEngine->getEventManagerInstance().gameOver;

    _pause = false;
    _gameOver = false;
    _levelComplete = false;
    _playedGameOver = false;
    _playedLevelComplete = false;

    if (!smilyDayMusic->isPlaying)
        smilyDayMusic->play();
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
    _ball = new Ball(_window, 400.0f, this, audioEngine); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    //_brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
    _brickManager->createBricks(1, 2, 1000.0f, 30.0f, 1.0f); // debug state

	// set level text
	_levelText.setString("Level: " + std::to_string(_level));

   
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
    
    

    if (_lives <= 0 && !_gameOver)
    {
        _gameOver = true;
        _masterText.setString(gameOverText);
		if (!_playedGameOver)
        {
            _playedGameOver = true;
            if(smilyDayMusic->isPlaying)
                smilyDayMusic->stop();
            gameOver->play();
        }

        return;
    }
    if (_gameOver)
    {   
         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
         {
            _gameOver = false;
            _playedGameOver = false;
            resetGame(gameOverText, 0);
         }
         return;
    }
    if (_brickManager->getBricks().size() == 0 && !_levelComplete)
    {
        _levelComplete = true;
        if (!_playedLevelComplete)
        {
            _playedLevelComplete = true;

            if(smilyDayMusic->isPlaying)
                smilyDayMusic->stop();
        }
		_masterText.setString(levelCompleteText);
        return;
    }
    if (_levelComplete)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            _levelComplete = false;
            _playedLevelComplete = false;
            resetGame(levelCompleteText, 1);

            if(!smilyDayMusic->isPlaying)
                smilyDayMusic->play();
            return;
        }
    }
    // pause and pause handling
    if (_pauseHold > 0.f)
        _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString(pauseText);
            _pauseHold = PAUSE_TIME_BUFFER;
            // pause the game sound here perhaps start with a stop feature here
            if(smilyDayMusic->isPlaying)
                smilyDayMusic->stop();
            // add pause sound here
            pause->play();
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
            // add pause sound here
            pause->play();
            // play game music here
            if(!smilyDayMusic->isPlaying)
                smilyDayMusic->play();
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

void GameManager::setLevelComplete(bool lC)
{
    _levelComplete = lC;
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
				_level = 0;

				deleteObjects();
				initialize();
                if (!smilyDayMusic->isPlaying)
                    smilyDayMusic->play();
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
				_level += levelIncrease;

				deleteObjects();
				initialize();

                if (!smilyDayMusic->isPlaying)
                    smilyDayMusic->play();
            }
    }
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }

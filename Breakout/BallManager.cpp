#include "BallManager.h"
#include "GameManager.h"

BallManager::BallManager(sf::RenderWindow* window, GameManager* gameMan, Engine* eng) : 
	_window(window), gameManager(gameMan), audioEngine(eng)
{
	initialise();
}

BallManager::~BallManager()
{
}

void BallManager::initialise()
{
	_balls.push_back(new Ball(_window, 400.0f, gameManager, audioEngine));
}

void BallManager::update(float dt)
{
	for (auto ball : _balls)
			ball->update(dt);
}

void BallManager::render()
{
	for (auto ball : _balls)
		ball->render();
}

// --- Powerups ---
//void BallManager::setSlowBall(float duration)
//{
//    if (duration) 
//    {
//        _isSlowBall = true;
//        _timeWithPowerupEffect = duration; 
//        return;
//    }
//    _isSlowBall = false;
//    _timeWithPowerupEffect = 0.f; 
//    audioEngine->getEventManagerInstance().gameMusic->setPitch(0.0f);
//}
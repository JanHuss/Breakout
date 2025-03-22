#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan)
    : PowerupBase(window, paddle, eng, ballMan)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFireBall::~PowerupFireBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }    
}

std::pair<POWERUPS, float> PowerupFireBall::applyEffect()
{
    audioEngine->getEventManagerInstance().fireBall->play();
    for(auto& ball : _ballManager->_balls)
        ball->setFireBall(5.0f);
    return { fireBall, 5.0f };
}
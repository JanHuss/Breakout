#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng, BallManager* ballMan)
    : PowerupBase(window, paddle, ball, eng, ballMan)
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
    _ball->setFireBall(5.0f);
    return { fireBall, 5.0f };
}
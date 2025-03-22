#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan)
    : PowerupBase(window, paddle, eng, ballMan)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    audioEngine->getEventManagerInstance().ballSpeed->setPitch(0.5f);
    audioEngine->getEventManagerInstance().ballSpeed->play();
    audioEngine->getEventManagerInstance().gameMusic->setPitch(0.3f);
    for(auto& ball : _ballManager->_balls)
    {
        ball->setFastBall(5.0f);
        ball->setVelocity(2.f, 5.0f);
    }
    return { fastBall, 5.0f };
}
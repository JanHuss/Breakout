#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle,/* Ball* ball,*/ Engine* eng, BallManager* ballMan)
    : PowerupBase(window, paddle,/* ball,*/ eng, ballMan)
{
    _sprite.setFillColor(ballEffectsColour); 
}

PowerupSlowBall::~PowerupSlowBall()
{
}

std::pair<POWERUPS, float> PowerupSlowBall::applyEffect()
{
    audioEngine->getEventManagerInstance().ballSpeed->setPitch(-0.1f);
    audioEngine->getEventManagerInstance().ballSpeed->play();
    audioEngine->getEventManagerInstance().gameMusic->setPitch(-0.3f);
    for (auto& ball : _ballManager->_balls)
    {
        ball->setSlowBall(5.0f);
        ball->setVelocity(0.5f, 5.0f);
    }
    return { ballSpeed, 5.0f };
}
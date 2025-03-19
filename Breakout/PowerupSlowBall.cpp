#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng)
    : PowerupBase(window, paddle, ball, eng)
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
    _ball->setVelocity(0.5f, 5.0f);
    return { ballSpeed, 5.0f };
}
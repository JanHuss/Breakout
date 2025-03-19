#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng)
    : PowerupBase(window, paddle, ball, eng)
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
    _ball->setVelocity(2.f, 5.0f);
    return { fastBall, 5.0f };
}
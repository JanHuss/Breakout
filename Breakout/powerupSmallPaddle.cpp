#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng)
    : PowerupBase(window, paddle, ball, eng)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
{
    // audio here
    audioEngine->getEventManagerInstance().paddleShrink->play();
    _paddle->setWidth(0.67f, 5.0f);
    _paddle->setSmallPaddle(5.0f);
    return { smallPaddle, 5.0f };
}
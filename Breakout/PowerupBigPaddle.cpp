#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle/*, Ball* ball*/, Engine* eng, BallManager* ballMan)
    : PowerupBase(window, paddle/*, ball*/, eng, ballMan)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
{
    audioEngine->getEventManagerInstance().paddleExpand->play();
    _paddle->setWidth(1.5f, 5.0f);
    _paddle->setBigPaddle(5.0f);
    return { bigPaddle, 5.0f };
}
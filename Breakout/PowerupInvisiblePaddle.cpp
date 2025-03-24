#include "PowerupInvisiblePaddle.h"

PowerupInvisiblePaddle::PowerupInvisiblePaddle(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan)
	: PowerupBase(window, paddle, eng, ballMan)
{

}

PowerupInvisiblePaddle::~PowerupInvisiblePaddle()
{
}

std::pair<POWERUPS, float> PowerupInvisiblePaddle::applyEffect()
{
	_paddle->setInvisiblePaddle(5.0f);
	return { invisiblePaddle, 5.0f };
}

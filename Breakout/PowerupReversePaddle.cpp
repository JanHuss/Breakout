#include "PowerupReversePaddle.h"

PowerupReversePaddle::PowerupReversePaddle(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan)
	: PowerupBase(window, paddle, eng, ballMan)
{
}

PowerupReversePaddle::~PowerupReversePaddle()
{
}

std::pair<POWERUPS, float> PowerupReversePaddle::applyEffect()
{
	// audio here
	_paddle->setReversePaddle(5.0f);
	return { reversePaddle, 5.0f };
}

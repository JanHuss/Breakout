#pragma once
#include "PowerupBase.h"
class PowerupInvisiblePaddle : public PowerupBase
{
	public:
    PowerupInvisiblePaddle(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan);
    ~PowerupInvisiblePaddle();

    std::pair<POWERUPS, float> applyEffect() override;
};


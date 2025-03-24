#pragma once
#include "PowerupBase.h"
class PowerupReversePaddle : public PowerupBase
{
public:
    PowerupReversePaddle(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan);
    ~PowerupReversePaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};


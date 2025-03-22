#pragma once

#include "PowerupManager.h"
#include "Engine.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle,/* Ball* ball,*/ Engine* eng, BallManager* ballMan);
    ~PowerupBigPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};

#pragma once
#include "PowerupBase.h"
class PowerupDoubleBall :
    public PowerupBase
{
public:
    PowerupDoubleBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng, BallManager* ballMan);
    ~PowerupDoubleBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};


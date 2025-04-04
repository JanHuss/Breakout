#pragma once
#include "PowerupBase.h"
class PowerupFastBall : public PowerupBase
{
public:
    PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan);
    ~PowerupFastBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};


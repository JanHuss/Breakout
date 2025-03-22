#pragma once

#include "PowerupBase.h"
#include "Engine.h"

class PowerupSlowBall : public PowerupBase
{
public:
    PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle,/* Ball* ball,*/ Engine* eng, BallManager* ballMan);
    ~PowerupSlowBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};

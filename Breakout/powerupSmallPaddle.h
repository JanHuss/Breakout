#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
private:
    float speed;
public:
    PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupSmallPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};

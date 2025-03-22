#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "PowerupBase.h"
#include "PowerupBigPaddle.h"
#include "PowerupSmallPaddle.h"
#include "PowerupSlowBall.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "PowerupDoubleBall.h"
#include "Paddle.h"
#include "BallManager.h"
#include "Ball.h"
#include "Engine.h"


class PowerupManager
{
public:
    PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng, BallManager* ballMan);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(); // Method to spawn a power-up
    void checkCollision(); // Check collision with paddle
    int getPowerupsSpawned();
    std::pair<POWERUPS, float> getPowerupInEffect();

private:
    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BallManager* _ballManager;
    std::vector<PowerupBase*> _powerups;            // used to manage deletion.
    std::optional<std::pair<POWERUPS, float>> _powerupInEffect;    // used for gameManager to get reference.
    
    // audio
    Engine* audioEngine;
};

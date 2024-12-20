#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
	void deleteObjects();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    void resetGame(std::string message, int levelIncrease);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;
    bool mouseInit;
    int level;

    sf::Font _font;
    sf::Text _masterText;
    sf::Text _levelText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    // strings
	std::string gameOverText;
	std::string pauseText;
	std::string levelCompleteText;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};

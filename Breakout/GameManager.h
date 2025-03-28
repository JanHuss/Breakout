#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "BallManager.h"
#include "MessagingSystem.h"
#include "UI.h"
//audio
#include "Engine.h"
#include "Component.h"


enum GAMESTATE {PLAY, PAUSE, GAMEOVER, LEVELCOMPLETE};

class GameManager {
public:
    GameManager(sf::RenderWindow* window, Engine* audioEng);
    void initialize();
	void deleteObjects();
    void update(float dt);
    void render();
    void handleInput(float dt);
    void updateGameState(float dt);
    void loseLife();
    //void setLevelComplete(bool lC);
    void powerupEffect(POWERUPS pu, float t);
    void resetGame(std::string message, int levelIncrease);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    GAMESTATE gameState;

    // sound bools
    bool _pause;
    bool _gameOver;
    bool _playedGameOver;
    bool _playedLevelComplete;
    bool _levelComplete;

    bool mouseInit;

    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    int _level;

    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;
    sf::Text _levelText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    //std::vector<Ball*> _balls;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    BallManager* _ballManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    // strings
	std::string gameOverText;
	std::string pauseText;
	std::string levelCompleteText;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn

    // audio
    Engine* audioEngine;
    Component* smilyDayMusic;
    Component* pause;
    Component* gameOver;
    Component* levelComplete;
};

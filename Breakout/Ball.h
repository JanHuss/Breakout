#pragma once
#include <SFML/Graphics.hpp>
//audio
#include "Engine.h"
#include "Component.h"


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, Engine* audioEng);
    ~Ball();
    void update(float dt);
    void render();
    void ballCollisions(float dt);
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setSlowBall(float duration);
    void setFastBall(float duration);
   
    void setExtraBall(float duration);
    void setMultiBall(float duration);

    void panToBallPosition();

    sf::CircleShape _sprite;
private:
    sf::CircleShape _fastBallSprite;
    sf::CircleShape _fastBallSpriteTwo;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    float _fastBallVelocity;
    bool _isAlive;
    bool _isFireBall;
    bool _isSlowBall;
    bool _isFastBall;
   
    
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;   
    static constexpr float FASTBALLRADIUSONE = 8.0f;
    static constexpr float FASTBALLRADIUSTWO = 6.0f;
    static constexpr float VELOCITY = 350.0f;   // for reference.

    // audio
    Engine* audioEngine;
    Component* paddle;
    Component* brick;
    Component* bounds;
};


#pragma once

#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Ball.h"

#include <vector>

class GameManager;

class BallManager
{
public:
	BallManager(sf::RenderWindow* window, GameManager* gameMan, Engine* eng);
	~BallManager();

	void initialise();
	void update(float dt);
	void render();

	// --- Powerups ---
	//void setSlowBall(float duration);
	void addBall();
	void removeBall();

	std::vector<Ball*> _balls;

private:
	sf::RenderWindow* _window;
	Engine* audioEngine;
	GameManager* gameManager;
	bool _isDoubleBall;
};


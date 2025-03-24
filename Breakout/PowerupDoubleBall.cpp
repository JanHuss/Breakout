#include "PowerupDoubleBall.h"

PowerupDoubleBall::PowerupDoubleBall(sf::RenderWindow* window, Paddle* paddle, Engine* eng, BallManager* ballMan)
	: PowerupBase(window, paddle, eng, ballMan)
{
	_sprite.setFillColor(extraBallEffectsColour); 
}

PowerupDoubleBall::~PowerupDoubleBall()
{
}

std::pair<POWERUPS, float> PowerupDoubleBall::applyEffect()
{
	_ballManager->addBall();
	return {multiBall, 10.0f};
}

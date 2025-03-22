#include "PowerupDoubleBall.h"

PowerupDoubleBall::PowerupDoubleBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, Engine* eng, BallManager* ballMan)
	: PowerupBase(window, paddle, ball, eng, ballMan)
{
	_sprite.setFillColor(extraBallEffectsColour); 
}

PowerupDoubleBall::~PowerupDoubleBall()
{
}

std::pair<POWERUPS, float> PowerupDoubleBall::applyEffect()
{
	return std::pair<POWERUPS, float>();
}

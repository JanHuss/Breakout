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
	return std::pair<POWERUPS, float>();
}

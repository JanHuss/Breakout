#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));

	brickLife = 0;
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_shape);
    }
}

sf::RectangleShape Brick::getShape()
{
    return _shape;
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Brick::setBrickColour()
{
	switch (brickColour)
	{
	case RED:
		_shape.setFillColor(sf::Color::Red);
		break;
	case AMBER:
		_shape.setFillColor(sf::Color::Yellow);
		break;
	case GREEN:
		_shape.setFillColor(sf::Color::Green);
		break;
	case SOLID:
		_shape.setFillColor(sf::Color::White);
		break;
	default:
		break;
	}
}

void Brick::setBrickLife(int bL)
{
	brickLife = bL;
}

int Brick::getBrickLife()
{
	return brickLife;
}

#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
	// create different colors for each brick depending on the rows they are in.
   // _shape.setFillColor(sf::Color::Red);
	if (y < 150)
		_shape.setFillColor(sf::Color::Green);
	if (y > 150 && y < 200)
		_shape.setFillColor(sf::Color::Yellow);
	if (y > 200 && y < 400)
        _shape.setFillColor(sf::Color::Red);
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

void Brick::setBrickLife()
{
	if (_shape.getFillColor() == sf::Color::Green)
		_shape.setFillColor(sf::Color::Yellow);
	else if (_shape.getFillColor() == sf::Color::Yellow)
		_shape.setFillColor(sf::Color::Red);
	else if (_shape.getFillColor() == sf::Color::Red)
		_isDestroyed = true;
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

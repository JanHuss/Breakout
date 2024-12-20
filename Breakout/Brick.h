#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::RectangleShape getShape();
    void setBrickLife();
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};
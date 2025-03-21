#pragma once
#include <SFML/Graphics.hpp>

enum BRICKCOLOUR {RED, AMBER, GREEN, SOLID};

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::RectangleShape getShape();
    sf::FloatRect getBounds() const;
    void setBrickColour();
    BRICKCOLOUR brickColour;

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};
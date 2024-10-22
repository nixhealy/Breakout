#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setPosition(sf::Vector2f pos) { _shape.setPosition(pos); }
    sf::Vector2f getPosition() { return _shape.getPosition(); }

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};
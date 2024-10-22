#pragma once
#include <SFML/Graphics.hpp>

class Particle {
public:
	Particle(int w, int h, int x, int y, int velx, int vely, sf::Color color);
	void render(sf::RenderWindow& window);
	void update(float dt);
	float getTime() { return _time; }
	sf::Vector2f getPosition() { return _shape.getPosition(); }

private:
	sf::RectangleShape _shape;
	sf::Vector2f _vel;
	float _time = 0;
};
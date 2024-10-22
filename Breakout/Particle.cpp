#include "Particle.h"

Particle::Particle(int w, int h, int x, int y, int velx, int vely, sf::Color color) {
	_shape.setSize(sf::Vector2f(w, h));
	_shape.setPosition(sf::Vector2f(x, y));
	_vel = sf::Vector2f(velx, vely);
	_shape.setFillColor(sf::Color(color.r, color.g, color.b, 128));
}

void Particle::update(float dt) {
	_shape.setPosition(sf::Vector2f(_shape.getPosition().x + _vel.x * dt, _shape.getPosition().y + _vel.y * dt));
	_vel.y += 9.8 * 10 * dt;
	_time += 1 * dt;
}

void Particle::render(sf::RenderWindow& window) {
	window.draw(_shape);
}
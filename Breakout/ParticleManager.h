#pragma once
#include <vector>
#include "Particle.h"

class ParticleManager {
public:
	ParticleManager(sf::RenderWindow* window);
	void createParticles(sf::Vector2f pos, sf::Color col);
	void update(float dt);
	void render();

private:
	std::vector<Particle*> _particles;
	sf::RenderWindow* _window;
};
#include "ParticleManager.h"

ParticleManager::ParticleManager(sf::RenderWindow* window)
    : _window(window)
{
}

void ParticleManager::createParticles(sf::Vector2f pos, sf::Color col) {
    int num = 10;
    for (int i = 0; i < num; i++) {
        int size = rand() % 10 + 10;
        Particle* p = new Particle(size, size, pos.x, pos.y, rand() % 200 - 100, rand() % 200 - 100, col);
        _particles.push_back(p);
    }
}

void ParticleManager::update(float dt) {
    for (int i = 0; i < _particles.size(); i++) {
        _particles[i]->update(dt);
        if (_particles[i]->getPosition().y > _window->getSize().y) {
            _particles.erase(_particles.begin() + i);
        }
    }
}

void ParticleManager::render() {
    for (Particle* p : _particles) {
        p->render(*_window);
    }
}
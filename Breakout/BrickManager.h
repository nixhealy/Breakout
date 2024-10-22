#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameManager; 
class ParticleManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
    void update(float dt);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;

    std::vector<sf::SoundBuffer> _buffers;
    sf::Sound _sound;
    int _combo = 0;
    float _time = 0;
};

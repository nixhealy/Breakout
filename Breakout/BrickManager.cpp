#include "BrickManager.h"
#include "GameManager.h"
#include "ParticleManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
    sf::SoundBuffer c;
    c.loadFromFile("audio/c.wav");
    _buffers.push_back(c);
    sf::SoundBuffer d;
    d.loadFromFile("audio/d.wav");
    _buffers.push_back(d);
    sf::SoundBuffer e;
    e.loadFromFile("audio/e.wav");
    _buffers.push_back(e);
    sf::SoundBuffer f;
    f.loadFromFile("audio/f.wav");
    _buffers.push_back(f);
    sf::SoundBuffer g;
    g.loadFromFile("audio/g.wav");
    _buffers.push_back(g);
    sf::SoundBuffer a;
    a.loadFromFile("audio/a.wav");
    _buffers.push_back(a);
    sf::SoundBuffer b;
    b.loadFromFile("audio/b.wav");
    _buffers.push_back(b);

    _shader.loadFromFile("brick_shader.frag", sf::Shader::Fragment);
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    _bricks.clear();

    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight);
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        if (_combo > 0) { brick.render(*_window, _shader); }
        else { brick.render(*_window); }
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        _gameManager->getParticleManager()->createParticles(sf::Vector2f(brick.getPosition().x + BRICK_WIDTH / 2, brick.getPosition().y + BRICK_HEIGHT / 2), sf::Color::Red);
        brick = _bricks.back();
        _bricks.pop_back();

        _combo++;
        _time = 0.f;
        if (_combo < 6) { _sound.setBuffer(_buffers[_combo]); }
        else { _sound.setBuffer(_buffers[6]); }
        _sound.play();

        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}

void BrickManager::update(float dt) {
    if (_combo > 0) {
        _time += dt;
        _fulltime += dt;
    }
    if (_time > 3) {
        _combo = 0;
        _time = 0;
        _fulltime = 0;
    }

    _shader.setUniform("time", _fulltime);
}
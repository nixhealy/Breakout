#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _particleManager(nullptr)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    _particleManager = new ParticleManager(_window);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    
    if (_isDead) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _masterText.setString("");
            _isDead = false;
            _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
            _lives = INITIAL_LIVES;
            _ui->lifeFill(_lives);
            delete _paddle;
            _paddle = new Paddle(_window);
            delete _ball;
            _ball = new Ball(_window, 400.0f, this);
            delete _powerupManager;
            _powerupManager = new PowerupManager(_window, _paddle, _ball);
        }
    }

    if (_lives <= 0)
    {
        _masterText.setString("Game over.\nPress space to restart.");
        _isDead = true;
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.\nPress space to restart.");
        _isDead = true;
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % 700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    if (sf::Mouse::getPosition(*_window).x > _paddle->getPosition())
    {
        _paddle->moveRight(dt * log10(sf::Mouse::getPosition(*_window).x - _paddle->getPosition()));
    }
    if (sf::Mouse::getPosition(*_window).x < _paddle->getPosition())
    {
        _paddle->moveLeft(dt * log10(_paddle->getPosition() - sf::Mouse::getPosition(*_window).x));;
    }

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _particleManager->update(dt);
    _brickManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
    _particleManager->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
ParticleManager* GameManager::getParticleManager() const { return _particleManager;  }
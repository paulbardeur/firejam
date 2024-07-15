/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Game
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.hpp"
#include "Firejam.hpp"
#include "LevelLoader.hpp"

Firejam::Game::Game(int level): _view(DEFAULT_VIEW), _isRunning(true), _score(NONE), _currentLevel(level), _infiniteMode(level == NONE)
{
    _scoreFont.loadFromFile(SCORE_FONT);

    _scoreText.setFont(_scoreFont);
    _scoreText.setCharacterSize(SCORE_SIZE);
    _scoreText.setFillColor(sf::Color::White);
    _scoreText.setPosition(SCORE_POSITION);

    updateScore();

    _backgroundTexture.loadFromFile(BACKGROUND_ASSET);
    _background.setTexture(_backgroundTexture);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Firejam::Game::loadLevel()
{
    _gems.clear();
    _obstacles.clear();
    _environments.clear();

    Firejam::LevelLoader::loadLevel(_currentLevel, _gems, _obstacles, _environments);

    _infiniteMode = false;
    _player = std::make_shared<Player>();
    _score = NONE;
    _isRunning = true;

    return SUCCESS;
}

int Firejam::Game::startInfiniteMode()
{
    _gems.clear();
    _obstacles.clear();
    _environments.clear();

    _infiniteMode = true;
    _player = std::make_shared<Player>();
    _score = NONE;
    _isRunning = true;

    _lastObstaclePosition = 800;
    _lastGemPosition = 800;

    generateInfiniteElements();

    return SUCCESS;
}

int Firejam::Game::generateInfiniteElements()
{
    float viewRightEdge = _view.getCenter().x + _view.getSize().x / 2;

    if (_lastObstaclePosition < viewRightEdge) {
        float obstacleX = _lastObstaclePosition + 200 + std::rand() % 500;
        float obstacleY = 500;
        _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(obstacleX, obstacleY), false));
        _lastObstaclePosition = obstacleX;
    }

    if (_lastGemPosition < viewRightEdge) {
        float gemX = _lastGemPosition + 50 + std::rand() % 150;
        float gemY = 450 + std::rand() % 50;
        Type gemType = (std::rand() % 2 == 0) ? Type::FIRE : Type::ICE;
        _gems.push_back(std::make_shared<Gem>(gemType, sf::Vector2f(gemX, gemY)));
        _lastGemPosition = gemX;
    }

    if (_lastEnvironmentPosition < viewRightEdge) {
        float envX = _lastEnvironmentPosition + 200 + std::rand() % 500;
        float envY = 500;
        Type envType = (std::rand() % 2 == 0) ? Type::FIRE : Type::ICE;
        _environments.push_back(std::make_shared<Environment>(envType, sf::Vector2f(envX, envY)));
        _lastEnvironmentPosition = envX;
    }

    auto obstacleIt = _obstacles.begin();
    while (obstacleIt != _obstacles.end()) {
        if (obstacleIt->get()->getBounds().left + obstacleIt->get()->getBounds().width < _view.getCenter().x - _view.getSize().x / 2) {
            obstacleIt = _obstacles.erase(obstacleIt);
            continue;
        }
        obstacleIt++;
    }

    auto gemIt = _gems.begin();
    while (gemIt != _gems.end()) {
        if (gemIt->get()->getBounds().left + gemIt->get()->getBounds().width < _view.getCenter().x - _view.getSize().x / 2) {
            gemIt = _gems.erase(gemIt);
            continue;
        }
        gemIt++;
    }

    auto envIt = _environments.begin();
    while (envIt != _environments.end()) {
        if (envIt->get()->getBounds().left + envIt->get()->getBounds().width < _view.getCenter().x - _view.getSize().x / 2) {
            envIt = _environments.erase(envIt);
            continue;
        }
        envIt++;
    }

    return SUCCESS;
}


int Firejam::Game::run(sf::RenderWindow &window)
{
    sf::Clock clock;

    if (_currentLevel == NONE) {
        startInfiniteMode();
    } else {
        loadLevel();
    }

    while (window.isOpen() && _isRunning) {

        processInput(window);

        sf::Time delta = clock.restart();

        update(delta, window);
        render(window);

    }

    _player = std::make_shared<Player>();

    sf::Vector2f playerPosition = _player.get()->getSprite().getPosition();

    _view.setCenter(playerPosition.x + VIEW_DELTA_X, _view.getCenter().y);
    window.setView(_view);

    return _score;
}

int Firejam::Game::processInput(sf::RenderWindow &window)
{
    sf::Event event;

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Space) {
                _player.get()->jump();
            }

        }

    }

    return SUCCESS;
}

int Firejam::Game::update(sf::Time delta, sf::RenderWindow &window)
{
    if (!_isRunning) {
        return SUCCESS;
    }

    _player.get()->move(delta);

    sf::Vector2f playerPosition = _player.get()->getSprite().getPosition();

    _view.setCenter(playerPosition.x + VIEW_DELTA_X, _view.getCenter().y);
    window.setView(_view);

    _scoreText.setPosition(_view.getCenter().x - 380, _view.getCenter().y - 285);
    _background.setPosition(_view.getCenter().x - 400, _view.getCenter().y - 300);

    auto gem = _gems.begin();

    while (gem != _gems.end()) {

        if (_player.get()->getBounds().intersects(gem->get()->getBounds())) {
            _player.get()->collectGem(gem->get()->getType());
            gem = _gems.erase(gem);
            _score += ONE_POINT;
            updateScore();
            continue;
        }

        gem++;

    }

    for (auto &env: _environments) {
        if (_player.get()->getBounds().intersects(env.get()->getBounds())) {
            if (_player.get()->getState() != env.get()->getType()) {
                _isRunning = false;
            }
        }
    }

    for (auto &obstacle: _obstacles) {
        if (_player.get()->handleCollision(obstacle.get()->getBounds(), obstacle.get()->getEnd())) {
            _isRunning = false;
        }
    }

    if (_infiniteMode) {
        generateInfiniteElements();
    }

    return SUCCESS;
}

int Firejam::Game::updateScore()
{
    _scoreText.setString(SCORE + std::to_string(_score));

    return SUCCESS;
}

int Firejam::Game::render(sf::RenderWindow &window)
{
    window.clear();

    window.draw(_background);

    for (auto &obstacle : _obstacles) {
        window.draw(obstacle.get()->getShape());
    }

    for (auto &env: _environments) {
        window.draw(env.get()->getSprite());

        sf::RectangleShape envHitbox;
        envHitbox.setPosition(env->getBounds().left, env->getBounds().top);
        envHitbox.setSize(sf::Vector2f(env->getBounds().width, env->getBounds().height));
        envHitbox.setFillColor(sf::Color::Transparent);
        envHitbox.setOutlineColor(sf::Color::White);
        envHitbox.setOutlineThickness(1.0f);
        window.draw(envHitbox);
    }

    for (auto &gem : _gems) {
        window.draw(gem.get()->getSprite());

        sf::RectangleShape gemHitbox;
        gemHitbox.setPosition(gem->getBounds().left, gem->getBounds().top);
        gemHitbox.setSize(sf::Vector2f(gem->getBounds().width, gem->getBounds().height));
        gemHitbox.setFillColor(sf::Color::Transparent);
        gemHitbox.setOutlineColor(sf::Color::White);
        gemHitbox.setOutlineThickness(1.0f);
        window.draw(gemHitbox);
    }

    window.draw(_player.get()->getSprite());

    sf::RectangleShape playerHitbox;
    playerHitbox.setPosition(_player.get()->getBounds().left, _player.get()->getBounds().top);
    playerHitbox.setSize(sf::Vector2f(_player.get()->getBounds().width, _player.get()->getBounds().height));
    playerHitbox.setFillColor(sf::Color::Transparent);
    playerHitbox.setOutlineColor(sf::Color::White);
    playerHitbox.setOutlineThickness(1.0f);
    window.draw(playerHitbox);

    window.draw(_scoreText);
    window.display();

    return SUCCESS;
}

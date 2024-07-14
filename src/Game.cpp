/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Game
*/

#include <iostream>

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

    // TODO PAUL // GENERATE INFINITY VECTOR OF OBJECTS //

    _infiniteMode = true;
    _player = std::make_shared<Player>();
    _score = NONE;
    _isRunning = true;

    return SUCCESS;
}

int Firejam::Game::run(sf::RenderWindow &window)
{
    sf::Clock clock;

    loadLevel();

    while (window.isOpen()) {

        processInput(window);

        sf::Time delta = clock.restart();

        update(delta, window);
        render(window);

    }

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
                window.close();
            }
        }
    }

    for (auto &obstacle: _obstacles) {
        if (_player.get()->handleCollision(obstacle.get()->getBounds(), obstacle.get()->getEnd())) {
            _isRunning = false;
            window.close();
        }
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

/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Game
*/

#include <iostream>

#include "Game.hpp"
#include "Firejam.hpp"

Firejam::Game::Game(void): _window(DEFAULT_WINDOW), _view(DEFAULT_VIEW), _isRunning(true), _score(NONE)
{
    initGame();
}

int Firejam::Game::initGame(void)
{
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(600, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(900, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(1200, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(1300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(1400, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(2300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(2300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(2400, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(2300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(3300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(3300, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::FIRE, sf::Vector2f(3400, 450)));
    _gems.push_back(std::make_shared<Gem>(Type::ICE, sf::Vector2f(3300, 450)));

    _environments.push_back(std::make_shared<Environment>(Type::FIRE, sf::Vector2f(700, 500)));
    _environments.push_back(std::make_shared<Environment>(Type::FIRE, sf::Vector2f(900, 500)));
    _environments.push_back(std::make_shared<Environment>(Type::FIRE, sf::Vector2f(1200, 500)));

    _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(400, 500)));
    _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(450, 500)));
    _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(500, 500)));
    _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(550, 500)));
    _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(550, 400)));
    _obstacles.push_back(std::make_shared<Obstacle>(sf::Vector2f(600, 400)));

    _scoreFont.loadFromFile(SCORE_FONT);

    _scoreText.setFont(_scoreFont);
    _scoreText.setCharacterSize(SCORE_SIZE);
    _scoreText.setFillColor(sf::Color::Red);
    _scoreText.setPosition(SCORE_POSITION);

    updateScore();

    return SUCCESS;
}

int Firejam::Game::run(void)
{
    sf::Clock clock;

    while (_window.isOpen()) {

        processInput();

        sf::Time delta = clock.restart();

        update(delta);
        render();

    }

    return SUCCESS;
}

int Firejam::Game::processInput(void)
{
    sf::Event event;

    while (_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            _window.close();
        }

        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Space) {
                _player.jump();
            }

        }

    }

    return SUCCESS;
}

int Firejam::Game::update(sf::Time delta)
{
    _player.move(delta);

    sf::Vector2f playerPosition = _player.getSprite().getPosition();

    _view.setCenter(playerPosition.x + VIEW_DELTA_X, _view.getCenter().y);
    _window.setView(_view);

    _scoreText.setPosition(_view.getCenter().x - 380, _view.getCenter().y - 285);

    auto gem = _gems.begin();

    while (gem != _gems.end()) {

        if (_player.getBounds().intersects(gem->get()->getBounds())) {
            _player.collectGem(gem->get()->getType());
            gem = _gems.erase(gem);
            _score += ONE_POINT;
            updateScore();
            continue;
        }

        gem++;

    }

    for (auto &env: _environments) {
        if (_player.getBounds().intersects(env.get()->getBounds())) {
            if (_player.getState() != env.get()->getType()) {
                _isRunning = false;
                _window.close();
            }
        }
    }

    for (auto &obstacle: _obstacles) {
        if (_player.handleCollision(obstacle.get()->getBounds())) {
            _isRunning = false;
            _window.close();
        }
    }

    return SUCCESS;
}

int Firejam::Game::updateScore()
{
    _scoreText.setString(SCORE + std::to_string(_score));

    return SUCCESS;
}

int Firejam::Game::render(void)
{
    _window.clear();

    for (auto &obstacle : _obstacles) {
        _window.draw(obstacle.get()->getShape());
    }

    for (auto &env: _environments) {
        _window.draw(env.get()->getSprite());

        sf::RectangleShape envHitbox;
        envHitbox.setPosition(env->getBounds().left, env->getBounds().top);
        envHitbox.setSize(sf::Vector2f(env->getBounds().width, env->getBounds().height));
        envHitbox.setFillColor(sf::Color::Transparent);
        envHitbox.setOutlineColor(sf::Color::White);
        envHitbox.setOutlineThickness(1.0f);
        _window.draw(envHitbox);
    }

    for (auto &gem : _gems) {
        _window.draw(gem.get()->getSprite());

        sf::RectangleShape gemHitbox;
        gemHitbox.setPosition(gem->getBounds().left, gem->getBounds().top);
        gemHitbox.setSize(sf::Vector2f(gem->getBounds().width, gem->getBounds().height));
        gemHitbox.setFillColor(sf::Color::Transparent);
        gemHitbox.setOutlineColor(sf::Color::White);
        gemHitbox.setOutlineThickness(1.0f);
        _window.draw(gemHitbox);
    }

    _window.draw(_player.getSprite());

    sf::RectangleShape playerHitbox;
    playerHitbox.setPosition(_player.getBounds().left, _player.getBounds().top);
    playerHitbox.setSize(sf::Vector2f(_player.getBounds().width, _player.getBounds().height));
    playerHitbox.setFillColor(sf::Color::Transparent);
    playerHitbox.setOutlineColor(sf::Color::White);
    playerHitbox.setOutlineThickness(1.0f);
    _window.draw(playerHitbox);

    _window.draw(_scoreText);
    _window.display();

    return SUCCESS;
}

/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Player
*/

#include <iostream>

#include "Player.hpp"
#include "Firejam.hpp"

Firejam::Player::Player(void): _state(Type::FIRE), _speed(DEFAULT_SPEED), _velocity(200, 0), _isJumping(false), _onGround(true), _onObstacle(false)
{
    _fireTexture.loadFromFile(FIRE_TEXTURE);
    _iceTexture.loadFromFile(ICE_TEXTURE);

    _sprite.setTexture(_fireTexture);
    _sprite.setPosition(INITIAL_POSITION);
}

int Firejam::Player::collectGem(Type gemType)
{
    if (_state == gemType) {
        return SUCCESS;
    }

    _state = gemType;
    updateSprite();

    return SUCCESS;
}

int Firejam::Player::move(sf::Time delta)
{
    float time = delta.asSeconds();

    if (!_onGround && !_onObstacle) {
        _velocity.y += GRAVITY * time;
    }

    sf::Vector2f movement(_velocity.x * time, _velocity.y * time);
    _sprite.move(_velocity * time);

    _onGround = false;
    _onObstacle = false;

    if (_sprite.getPosition().y >= GROUND_LEVEL) {
        _sprite.setPosition(_sprite.getPosition().x, GROUND_LEVEL);
        _velocity.y = NONE;
        _onGround = true;
        _isJumping = false;
    }

    return SUCCESS;
}

int Firejam::Player::jump()
{
    if (_onGround || _onObstacle) {
        _velocity.y = JUMP_FORCE;
        _onGround = false;
        _onObstacle = false;
        _isJumping = true;
    }

    return SUCCESS;
}

bool Firejam::Player::handleCollision(const sf::FloatRect &bounds)
{
    if (!getBounds().intersects(bounds)) {
        return false;
    }

    _onObstacle = true;

    if (_velocity.y > NONE && _sprite.getPosition().y + getBounds().height - _velocity.y * 0.1f <= bounds.top) {
        _sprite.setPosition(_sprite.getPosition().x, bounds.top - getBounds().height - 14);
        _velocity.y = NONE;
        _onGround = false;
        _onObstacle = true;
        _isJumping = false;
        return false;
    }

    if (getBounds().left < bounds.left && getBounds().height > bounds.top - 1) {
        return true;
    }

    if (bounds.top < getBounds().top && getBounds().top < bounds.top + bounds.height) {
        std::cout << "passer ici\n";
        return true;
    }

    return false;
}

int Firejam::Player::updateSprite()
{
    if (_state == Type::FIRE) {
        _sprite.setTexture(_fireTexture);
    }

    if (_state == Type::ICE) {
        _sprite.setTexture(_iceTexture);
    }

    return SUCCESS;
}

sf::FloatRect Firejam::Player::getBounds() const
{
    sf::FloatRect rectangle = _sprite.getGlobalBounds();

    rectangle.height -= 30;
    rectangle.top += 15;
    rectangle.width -= 20;
    rectangle.left += 10;

    return rectangle;
}
/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Player
*/

#include "Player.hpp"
#include "Firejam.hpp"

Firejam::Player::Player(void): _state(Type::FIRE), _speed(DEFAULT_SPEED), _velocity(NONE), _isJumping(false)
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

    _sprite.move(_speed * time, NONE);

    if (_isJumping) {

        _sprite.move(NONE, _velocity * time);

        _velocity += GRAVITY * time;

        if (_sprite.getPosition().y >= GROUND_LEVEL) {
            _sprite.setPosition(_sprite.getPosition().x, GROUND_LEVEL);
            _isJumping = false;
        }

    }

    return SUCCESS;
}


int Firejam::Player::jump()
{
    if (_isJumping) {
        return SUCCESS;
    }

    _isJumping = true;
    _velocity = JUMP_FORCE;

    return SUCCESS;
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
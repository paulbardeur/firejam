/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Gem
*/

#include <iostream>

#include "Gem.hpp"

Firejam::Gem::Gem(Type type, sf::Vector2f position) : _type(type)
{
    if (type == Type::FIRE) {
        _texture.loadFromFile(GEM_FIRE_TEXTURE);
    }

    if (type == Type::ICE) {
        _texture.loadFromFile(GEM_ICE_TEXTURE);
    }

    _sprite.setTexture(_texture);
    _sprite.setPosition(position);
}

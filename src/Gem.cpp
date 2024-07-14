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

sf::FloatRect Firejam::Gem::getBounds() const
{
    sf::FloatRect rectangle = _sprite.getGlobalBounds();

    rectangle.height -= 15;
    rectangle.top += 10;
    rectangle.width -= 10;
    rectangle.left += 5;

    return rectangle;
}

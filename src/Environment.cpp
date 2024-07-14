/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Environment
*/

#include "Environment.hpp"

Firejam::Environment::Environment(Type type, sf::Vector2f position): _type(type)
{
    if (type == Type::FIRE) {
        _texture.loadFromFile("assets/point_fire.png");
    }

    if (type == Type::ICE) {
        _texture.loadFromFile("assets/point_ice.png");
    }

    _sprite.setPosition(position);
    _sprite.setTexture(_texture);
}

sf::FloatRect Firejam::Environment::getBounds() const
{
    sf::FloatRect rectangle = _sprite.getGlobalBounds();

    rectangle.top += 5;

    return rectangle;
}

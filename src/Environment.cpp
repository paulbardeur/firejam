/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Environment
*/

#include "Environment.hpp"

Firejam::Environment::Environment(Type type, sf::FloatRect area) : _type(type)
{
    _shape.setPosition(area.left, area.top);
    _shape.setSize(sf::Vector2f(area.width, area.height));

    if (type == Type::FIRE) {
        _shape.setFillColor(sf::Color::Red);
    }

    if (type == Type::ICE) {
        _shape.setFillColor(sf::Color::Blue);
    }

}

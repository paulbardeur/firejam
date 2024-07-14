/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Obstacle
*/

#include "Obstacle.hpp"

Firejam::Obstacle::Obstacle(sf::Vector2f position, bool end): _end(end)
{
    if (end) {
        _shape.setFillColor(sf::Color::Green);
    } else {
        _shape.setFillColor(sf::Color::Blue);
    }

    _shape.setSize(sf::Vector2f(50, 50));
    _shape.setOutlineColor(sf::Color::White);
    _shape.setOutlineThickness(3);
    _shape.setPosition(position);
}

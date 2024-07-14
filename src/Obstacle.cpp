/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Obstacle
*/

#include "Obstacle.hpp"

Firejam::Obstacle::Obstacle(sf::Vector2f position)
{
    _shape.setSize(sf::Vector2f(45, 45));
    _shape.setFillColor(sf::Color::Blue);
    _shape.setOutlineColor(sf::Color::White);
    _shape.setOutlineThickness(3);
    _shape.setPosition(position);
}

/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Obstacle
*/

#include "Obstacle.hpp"

Firejam::Obstacle::Obstacle(sf::Vector2f position)
{
    _texture.loadFromFile(OBSTACLE_TEXTURE);

    _sprite.setTexture(_texture);
    _sprite.setPosition(position);
}

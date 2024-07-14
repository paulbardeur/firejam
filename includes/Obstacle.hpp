/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Obstacle
*/

#ifndef OBSTACLE_HPP_
    #define OBSTACLE_HPP_

    #include <SFML/Graphics.hpp>

    #define OBSTACLE_TEXTURE "assets/ostacle.png"

namespace Firejam {

    class Obstacle {

        public:

            Obstacle(sf::Vector2f position);

            sf::FloatRect getBounds() const { return _shape.getGlobalBounds(); };
            sf::RectangleShape getShape() const { return _shape; };
 
        private:

            sf::RectangleShape _shape;

    };

;}

#endif /* !OBSTACLE_HPP_ */

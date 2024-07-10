/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Obstacle
*/

#ifndef OBSTACLE_HPP_
    #define OBSTACLE_HPP_

    #include <SFML/Graphics.hpp>

namespace Firejame {

    class Obstacle {

        public:

            Obstacle(sf::Vector2f position);

            sf::FloatRect getBounds() const;
            sf::Sprite getSprite() const;
 
        private:

            sf::Sprite _sprite;
            sf::Texture _texture;

    };

;}

#endif /* !OBSTACLE_HPP_ */

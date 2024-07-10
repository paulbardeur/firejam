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

            sf::FloatRect getBounds() const { return _sprite.getGlobalBounds(); };
            sf::Sprite getSprite() const { return _sprite; };
 
        private:

            sf::Sprite _sprite;
            sf::Texture _texture;

    };

;}

#endif /* !OBSTACLE_HPP_ */

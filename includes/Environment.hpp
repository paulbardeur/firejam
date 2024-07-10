/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Environment
*/

#ifndef ENVIRONMENT_HPP_
    #define ENVIRONMENT_HPP_

    #include <SFML/Graphics.hpp>

    #include "Player.hpp"

namespace Firejam {

    class Environment {

        public:

            Environment(Type type, sf::FloatRect area);

            Type getType() const { return _type; };
            sf::FloatRect getBounds() const { return _shape.getGlobalBounds(); };
            sf::RectangleShape getSprite() const { return _shape; };
 
        private:

            Type _type;
            sf::RectangleShape _shape;

    };

;}

#endif /* !ENVIRONMENT_HPP_ */

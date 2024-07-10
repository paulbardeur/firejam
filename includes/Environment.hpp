/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Environment
*/

#ifndef ENVIRONMENT_HPP_
    #define ENVIRONMENT_HPP_

    #include <SFML/Graphics.hpp>

namespace Firejame {

    enum class EnvironmentType { FIRE, ICE };

    class Environment {

        public:

            Environment(EnvironmentType type, sf::FloatRect area);

            EnvironmentType getType() const;
            sf::FloatRect getBounds() const;
            sf::Sprite getSprite() const;
 
        private:

            EnvironmentType _type;
            sf::RectangleShape _shape;

    };

;}

#endif /* !ENVIRONMENT_HPP_ */

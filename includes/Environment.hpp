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

            Environment(Type type, sf::Vector2f position);

            Type getType() const { return _type; };
            sf::Sprite getSprite() const { return _sprite; };

            sf::FloatRect getBounds() const;
 
        private:

            Type _type;
            sf::Sprite _sprite;
            sf::Texture _texture;

    };

;}

#endif /* !ENVIRONMENT_HPP_ */

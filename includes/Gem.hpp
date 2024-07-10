/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Gem
*/

#ifndef GEM_HPP_
    #define GEM_HPP_

    #include <SFML/Graphics.hpp>

    #include "Player.hpp"

    #define GEM_FIRE_TEXTURE "assets/gem_fire.png"
    #define GEM_ICE_TEXTURE "assets/gem_ice.png"

namespace Firejam {

    class Gem {

        public:

            Gem(Type type, sf::Vector2f position);

            Type getType() const { return _type; };
            sf::FloatRect getBounds() const { return _sprite.getGlobalBounds(); };
            sf::Sprite getSprite() const { return _sprite; };

        private:

            Type _type;
            sf::Sprite _sprite;
            sf::Texture _texture;

    };

;}

#endif /* !GEM_HPP_ */

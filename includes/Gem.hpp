/*
** EPITECH PROJECT, 2024
** Firejam
** File description:
** Gem
*/

#ifndef GEM_HPP_
    #define GEM_HPP_

    #include <SFML/Graphics.hpp>

namespace Firejame {

    enum GemType { FIRE, ICE };

    class Gem {

        public:

            Gem(GemType type, sf::Vector2f position);

            GemType getType() const;
            sf::FloatRect getBounds() const;
            sf::Sprite getSprite() const;
 
        private:

            GemType _type;
            sf::Sprite _sprite;
            sf::Texture _texture;

    };

;}

#endif /* !GEM_HPP_ */
